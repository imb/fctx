/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

FCT (Fast C Test) Unit Testing Framework

Copyright (c) 2008, Ian Blumel (ian.blumel@gmail.com)
All rights reserved.

This license is based on the BSD License.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution.

    * Neither the name of, Ian Blumel, nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
====================================================================

File: fct.h
*/

#if !defined(FCT_INCLUDED__IMB)
#define FCT_INCLUDED__IMB

#define FCT_VERSION_MAJOR 1
#define FCT_VERSION_MINOR 1
#define FCT_VERSION_MICRO 1

#define _FCT_QUOTEME(x) #x
#define FCT_QUOTEME(x) _FCT_QUOTEME(x)

#define FCT_VERSION_STR (FCT_QUOTEME(FCT_VERSION_MAJOR) "."\
                         FCT_QUOTEME(FCT_VERSION_MINOR) "."\
                         FCT_QUOTEME(FCT_VERSION_MICRO))
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <ctype.h>

#define FCT_MAX_NAME           256
#define FCT_MAX_LOG_LINE       256

#define nbool_t int
#define FCT_TRUE   1
#define FCT_FALSE  0

#define FCTMIN(x, y) ( x < y) ? (x) : (y)

/* Forward declarations. The following forward declarations are required
because there is a inter-relationship between certain objects that
just can not be untwined. */
typedef struct _fct_logger_i fct_logger_i;
typedef struct _fct_standard_logger_t fct_standard_logger_t;
typedef struct _fct_minimal_logger_t fct_minimal_logger_t;
typedef struct _fctchk_t fctchk_t;
typedef struct _fct_test_t fct_test_t;
typedef struct _fct_ts_t fct_ts_t;
typedef struct _fctkern_t fctkern_t;

/* Forward declare some functions used throughout. */
static fct_standard_logger_t *
fct_standard_logger__new(void);

static void
fct_logger__del(fct_logger_i *logger);

static void
fct_logger__on_cndtn(fct_logger_i *self, fctchk_t const *chk);

static void
fct_logger__on_test_start(fct_logger_i *logger, fct_test_t const *test);

static void
fct_logger__on_test_end(fct_logger_i *logger, fct_test_t const *test);

static void
fct_logger__on_test_suite_start(fct_logger_i *logger, fct_ts_t const *ts);

static void
fct_logger__on_test_suite_end(fct_logger_i *logger, fct_ts_t const *ts);

static void
fct_logger__on_warn(fct_logger_i *logger, char const *warn);



/* Explicitly indicate a no-op */
#define fct_pass()

#define fct_unused(x)  (void)(x)

/* This is just a little trick to let me put comments inside of macros. I
really only want to bother with this when we are "unwinding" the macros
for debugging purposes. */
#if defined(FCT_CONF_UNWIND)
#	define _fct_cmt(string)		{char*_=string;}
#else
#	define _fct_cmt(string)
#endif

/*
--------------------------------------------------------
UTILITIES
--------------------------------------------------------
*/

/* Utility for truncated, safe string copies. The NUM
should be the length of DST plus the null-termintor. */
static void
fct_safe_str_cpy(char *dst, char const *src, size_t num)
{
    assert( dst != NULL );
    assert( src != NULL );
    assert( num > 0 );
#if defined(WIN32) && _MSC_VER >= 1400
    strncpy_s(dst, num, src, _TRUNCATE);
#else
    strncpy(dst, src, num);
#endif
    dst[num-1] = '\0';
}

/* Isolate the vsnprintf implementation */
static int
fct_vsnprintf(char *buffer,
              size_t buffer_len,
              char const *format,
              va_list args)
{
    int count =0;
    /* Older microsoft compilers where not ANSI compliant with this
    function and you had to use _vsnprintf. I will assume that newer
    Microsoft Compilers start implementing vsnprintf. */
#if defined(_MSC_VER) && (_MSC_VER < 1400)
    count = _vsnprintf(buffer, buffer_len, format, args);
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
    count = vsnprintf_s(buffer, buffer_len, _TRUNCATE, format, args);
#else
    count = vsnprintf(buffer, buffer_len, format, args);
#endif
    return count;
}


/* Isolate the snprintf implemenation. */
static int
fct_snprintf(char *buffer, size_t buffer_len, char const *format, ...)
{
    int count =0;
    va_list args;
    va_start(args, format);
    count =fct_vsnprintf(buffer, buffer_len, format, args);
    va_end(args);
    return count;
}


/* Helper to for cloning strings on the heap. Returns NULL for
an out of memory condition. */
static char*
fct_str_clone(char const *s)
{
    char *k =NULL;
    size_t klen =0;
    assert( s != NULL && "invalid arg");
    klen = strlen(s)+1;
    k = (char*)malloc(sizeof(char)*klen+1);
    fct_safe_str_cpy(k, s, klen);
    return k;
}



/* A very, very simple "filter". This just compares the supplied prefix
against the test_str, to see if they both have the same starting
characters. If they do we return true, otherwise we return false. If the
prefix is a blank string or NULL, then it will return FCT_TRUE.*/
static nbool_t
fct_filter_pass(char const *prefix, char const *test_str)
{
    nbool_t is_match = FCT_FALSE;
    char const *prefix_p;
    char const *test_str_p;

    /* If you got nothing to test against, why test? */
    assert( test_str != NULL );

    /* When the prefix is NULL or blank, we always return FCT_TRUE. */
    if ( prefix == NULL  || prefix[0] == '\0' )
    {
        return FCT_TRUE;
    }

    /* Iterate through both character arrays at the same time. We are
    going to play a game and see if we can beat the house. */
    for ( prefix_p = prefix, test_str_p = test_str;
            *prefix_p != '\0' && *test_str_p != '\0';
            ++prefix_p, ++test_str_p )
    {
        is_match = *prefix_p == *test_str_p;
        if ( !is_match )
        {
            break;   /* Quit the first time we don't match. */
        }
    }

    /* If the iterator for the test_str is pointing at the null char, and
    the iterator for the prefix string is not, then the prefix string is
    larger than the actual test string, and therefore we failed to pass the
    filter. */
    if ( *test_str_p == '\0' && *prefix_p != '\0' )
    {
        return FCT_FALSE;
    }

    /* is_match will be set to the either FCT_TRUE if we kicked of the loop
    early because our filter ran out of characters or FCT_FALSE if we
    encountered a mismatch before our filter ran out of characters. */
    return is_match;
}


/* Small little predicates to use with fct_str_eq function. */
static int
_fct_check_char(char a, char b)
{
    return a == b;
}

static int
_fct_check_char_lower(char a, char b)
{
    return tolower(a) == tolower(b);
}


/* Routine checks if two strings match according to a CHECK_CHAR.
The check is done char-by-char, and if predicate is not satisfied,
false is returned. */
static int
_fct_str_equal(char const *v1,
               char const *v2,
               int (*check_char)(char, char))
{
    char const *pv1 = NULL;
    char const *pv2 = NULL;

    if ( v1 == NULL && v2 == NULL )
    {
        return 1;
    }
    else if ( (v1 != NULL && v2 == NULL) || (v1 == NULL && v2 != NULL) )
    {
        return 0;
    }

    for ( pv1 = v1, pv2 = v2; *pv1 != '\0' && *pv2 != '\0'; ++pv1, ++pv2)
    {
        if ( !check_char(*pv1, *pv2) )
        {
            return 0;   /* mismatch! */
        }
    }
    if ( (*pv1 == '\0' && *pv2 != '\0') || (*pv1 != '\0' && *pv2 == '\0') )
    {
        /* Different length strings implies they are not equal. */
        return 0;
    }
    return 1; /* Same length strings, never failed to mismatch. */
}



/*
--------------------------------------------------------
TIMER
--------------------------------------------------------
*/

typedef struct _fct_timer_t fct_timer_t;
struct _fct_timer_t
{
    clock_t start;
    clock_t stop;
    double duration;
};


static void
fct_timer__init(fct_timer_t *timer)
{
    assert(timer != NULL);
    memset(timer, 0, sizeof(fct_timer_t));
}


static void
fct_timer__start(fct_timer_t *timer)
{
    assert(timer != NULL);
    timer->start = clock();
}


static void
fct_timer__stop(fct_timer_t *timer)
{
    assert(timer != NULL);
    timer->stop = clock();
    timer->duration = (double) (timer->stop - timer->start) / CLOCKS_PER_SEC;
}


/* Returns the time in seconds. */
static double
fct_timer__duration(fct_timer_t *timer)
{
    assert( timer != NULL );
    return timer->duration;
}


/*
--------------------------------------------------------
GENERIC LIST
--------------------------------------------------------
*/

/* For now we will just keep it at a linear growth rate. */
#define FCT_LIST_GROWTH_FACTOR   2

/* Starting size for the list, to keep it simple we will start
at a reasonable size. */
#define FCT_LIST_START_SIZE      8

/* Helper macros for quickly iterating through a list. You should be able
to do something like,

  FCT_NLIST_FOREACH_BGN(fct_logger_i*, logger, my_list)
  {
     fct_logger__on_blah(logger);
  }
  FCT_NLIST_FOREACH_END();

*/
#define FCT_NLIST_FOREACH_BGN(Type, Var, List)\
{\
   if ( List != NULL ) {\
      size_t item_i##Var;\
      size_t num_items##Var = fct_nlist__size(List);\
      for( item_i##Var =0; item_i##Var != num_items##Var; ++item_i##Var )\
      {\
         Type Var = (Type) fct_nlist__at((List), item_i##Var);

#define FCT_NLIST_FOREACH_END() }}}

/* Used to manage a list of loggers. This works mostly like
the STL vector, where the array grows as more items are
appended. */
typedef struct _fct_nlist_t fct_nlist_t;
struct _fct_nlist_t
{
    /* Item's are stored as pointers to void. */
    void **itm_list;

    /* Indicates the number of element's in the array. */
    size_t avail_itm_num;

    /* Indicates the number of actually elements in the array. */
    size_t used_itm_num;
};
typedef void (*fct_nlist_on_del_t)(void*);


/* Clears the contents of the list, and sets the list count to 0. The
actual count remains unchanged. If on_del is supplied it is executed
against each list element. */
static void
fct_nlist__clear(fct_nlist_t *list, fct_nlist_on_del_t on_del)
{
    size_t itm_i__ =0;
    assert( list != NULL );
    if ( on_del != NULL )
    {
        for ( itm_i__=0; itm_i__ != list->used_itm_num; ++itm_i__ )
        {
            on_del(list->itm_list[itm_i__]);
        }
    }
    list->used_itm_num =0;
}


/* If you used init, then close with final. This is useful for
working with structures that live on the stack. */
static void
fct_nlist__final(fct_nlist_t *list, fct_nlist_on_del_t on_del)
{
    assert( list != NULL );
    fct_nlist__clear(list, on_del);
    free(list->itm_list);
}


/* Initializes a list. Useful for populating existing structures.
Returns 0 if there was an error allocating memory. Returns 1 otherwise. */
static int
fct_nlist__init(fct_nlist_t *list)
{
    assert( list != NULL );

    list->itm_list = (void**)malloc(sizeof(void*)*FCT_LIST_START_SIZE);
    if ( list->itm_list == NULL )
    {
        return 0;
    }

    list->avail_itm_num =FCT_LIST_START_SIZE;
    list->used_itm_num =0;

    return 1;
}


/* Returns the number of elements within the list. */
static size_t
fct_nlist__size(fct_nlist_t const *list)
{
    assert( list != NULL );
    return list->used_itm_num;
}


/* Returns the item at idx, asserts otherwise. */
static void*
fct_nlist__at(fct_nlist_t const *list, size_t idx)
{
    assert( list != NULL );
    assert( idx < list->used_itm_num );
    return list->itm_list[idx];
}


static void
fct_nlist__append(fct_nlist_t *list, void *itm)
{
    assert( list != NULL );
    assert( list->itm_list != NULL );
    assert( list->avail_itm_num != 0 );

    /* If we ran out of room, then the last increment should be equal to the
    available space, in this case we need to grow a little more. */
    if ( list->used_itm_num == list->avail_itm_num )
    {
        list->avail_itm_num = list->avail_itm_num*FCT_LIST_GROWTH_FACTOR;
        list->itm_list = (void**)realloc(
                             list->itm_list, sizeof(void*)*list->avail_itm_num
                         );
        assert( list->itm_list != NULL && "memory check");
    }

    list->itm_list[list->used_itm_num] = itm;
    ++(list->used_itm_num);
}



/*
-----------------------------------------------------------
A SINGLE CHECK
-----------------------------------------------------------
This defines a single check. It indicates what the check was,
and where it occurred. A "Test" object will have-a bunch
of "checks".
*/

struct _fctchk_t
{
    /* This string that represents the condition. */
    char cndtn[FCT_MAX_LOG_LINE];

    /* These indicate where the condition occurred. */
    char file[FCT_MAX_LOG_LINE];

    int lineno;

    nbool_t is_pass;

    /* This is a message that we can "format into", if
    no format string is specified this should be
    equivalent to the cntdn. */
    char msg[FCT_MAX_LOG_LINE];
};

#define fctchk__is_pass(_CHK_) ((_CHK_)->is_pass)
#define fctchk__file(_CHK_)    ((_CHK_)->file)
#define fctchk__lineno(_CHK_)  ((_CHK_)->lineno)
#define fctchk__cndtn(_CHK_)   ((_CHK_)->cndtn)
#define fctchk__msg(_CHK_)     ((_CHK_)->msg)

static fctchk_t*
fctchk_new(int is_pass,
           char const *cndtn,
           char const *file,
           int lineno,
           char const *format,
           va_list args)
{
    fctchk_t *chk = NULL;

    assert( cndtn != NULL );
    assert( file != NULL );
    assert( lineno > 0 );

    chk = (fctchk_t*)calloc(1, sizeof(fctchk_t));
    if ( chk == NULL )
    {
        return NULL;
    }

    fct_safe_str_cpy(chk->cndtn, cndtn, FCT_MAX_LOG_LINE);
    fct_safe_str_cpy(chk->file, file, FCT_MAX_LOG_LINE);
    chk->lineno = lineno;

    chk->is_pass =is_pass;

    if ( format != NULL )
    {
        fct_vsnprintf(chk->msg, FCT_MAX_LOG_LINE, format, args);
    }
    else
    {
        /* Default to make the condition be the message, if there was no format
        specified. */
        fct_safe_str_cpy(chk->msg, cndtn, FCT_MAX_LOG_LINE);
    }

    return chk;
}


/* Cleans up a "check" object. If the `chk` is NULL, this function does
nothing. */
static void
fctchk__del(fctchk_t *chk)
{
    if ( chk == NULL )
    {
        return;
    }
    free( chk );
}


/*
-----------------------------------------------------------
A TEST
-----------------------------------------------------------
A suite will have-a list of tests. Where each test will have-a
list of failed and passed checks.
*/

struct _fct_test_t
{
    /* List of failed and passed "checks" (fctchk_t). Two seperate
    lists make it faster to determine how many checks passed and how
    many checks failed. */
    fct_nlist_t failed_chks;
    fct_nlist_t passed_chks;

    /* The name of the test case. */
    char name[FCT_MAX_NAME];
};

#define fct_test__name(_TEST_) ((_TEST_)->name)

/* Clears the failed tests ... partly for internal testing. */
#define fct_test__clear_failed(test) \
    fct_nlist__clear(test->failed_chks, (fct_nlist_on_del_t)fctchk__del);\
 

static void
fct_test__del(fct_test_t *test)
{
    if (test == NULL )
    {
        return;
    }
    fct_nlist__final(&(test->passed_chks), (fct_nlist_on_del_t)fctchk__del);
    fct_nlist__final(&(test->failed_chks), (fct_nlist_on_del_t)fctchk__del);
    free(test);
}

static fct_test_t*
fct_test_new(char const *name)
{
    nbool_t ok =FCT_FALSE;
    fct_test_t *test =NULL;

    test = (fct_test_t*)malloc(sizeof(fct_test_t));
    if ( test == NULL )
    {
        return NULL;
    }

    fct_safe_str_cpy(test->name, name, FCT_MAX_NAME);

    if ( !fct_nlist__init(&(test->failed_chks))
            || !fct_nlist__init(&(test->passed_chks)) )
    {
        ok =FCT_FALSE;
        goto finally;
    }

    ok =FCT_TRUE;
finally:
    if ( !ok )
    {
        fct_test__del(test);
        test =NULL;
    }
    return test;
}


static nbool_t
fct_test__is_pass(fct_test_t const *test)
{
    assert( test != NULL );
    return fct_nlist__size(&(test->failed_chks)) == 0;
}


static void
fct_test__add(fct_test_t *test, fctchk_t *chk)
{

    assert( test != NULL );
    assert( chk != NULL );

    if ( fctchk__is_pass(chk) )
    {
        fct_nlist__append(&(test->passed_chks), (void*)chk);
    }
    else
    {
        fct_nlist__append(&(test->failed_chks), (void*)chk);
    }
}

/* Returns the number of checks made throughout the test. */
static size_t
fct_test__chk_cnt(fct_test_t const *test)
{
    assert( test != NULL );
    return fct_nlist__size(&(test->failed_chks)) \
           + fct_nlist__size(&(test->passed_chks));
}






/*
-----------------------------------------------------------
TEST SUITE (TS)
-----------------------------------------------------------
*/


/* The different types of 'modes' that a test suite can be in.

While the test suite is iterating through all the tests, its "State"
can change from "setup mode", to "test mode" to "tear down" mode.
These help to indicate what mode are currently in. Think of it as a
basic FSM.

            if the count was 0                               end
           +--------->---------------------> ending_mode-----+
           |                                       ^
           ^                                       |
start      |                              [if no more tests]
  |        |                                       |
  +-count_mode -> setup_mode -> test_mode -> teardown_mode
                      ^                           |
                      +-----------<---------------+
*/
enum ts_mode
{
    ts_mode_cnt,         /* To setup when done counting. */
    ts_mode_setup,       /* To test when done setup. */
    ts_mode_teardown,    /* To ending mode, when no more tests. */
    ts_mode_test,        /* To tear down mode. */
    ts_mode_ending,      /* To ... */
    ts_mode_end          /* .. The End. */
};

/* Types of states the test could be in. */
typedef enum
{
    fct_test_status_SUCCESS,
    fct_test_status_FAILURE
} fct_test_status;


struct _fct_ts_t
{
    /* For counting our 'current' test number, and the total number of
    tests. */
    int  curr_test_num;
    int  total_test_num;

    /* Keeps track of the current state of the object while it is walking
    through its "FSM" */
    enum ts_mode mode;

    /* The name of the test suite. */
    char name[FCT_MAX_NAME];

    /* List of tests that where executed within the test suite. */
    fct_nlist_t test_list;
};


#define fct_ts__is_setup_mode(ts)     ((ts)->mode == ts_mode_setup)
#define fct_ts__is_teardown_mode(ts)  ((ts)->mode == ts_mode_teardown)
#define fct_ts__is_test_mode(ts)      ((ts)->mode == ts_mode_test)
#define fct_ts__is_ending_mode(ts)    ((ts)->mode == ts_mode_ending)
#define fct_ts__is_end(ts)            ((ts)->mode == ts_mode_end)
#define fct_ts__is_cnt_mode(ts)       ((ts)->mode == ts_mode_cnt)

/* This cndtn is set when we have iterated through all the tests, and
there was nothing more to do. */
#define fct_ts__ending(ts)          ((ts)->mode = ts_mode_ending)

/* Flag a test suite as complete. It will no longer accept any more tests. */
#define fct_ts__end(ts)  ((ts)->mode = ts_mode_end)

#define fct_ts__name(ts)              ((ts)->name)


static void
fct_ts__del(fct_ts_t *ts)
{
    if ( ts == NULL )
    {
        return;
    }
    fct_nlist__final(&(ts->test_list), (fct_nlist_on_del_t)fct_test__del);
    free(ts);
}

static fct_ts_t *
fct_ts_new(char const *name)
{
    fct_ts_t *ts =NULL;
    ts = (fct_ts_t*)calloc(1, sizeof(fct_ts_t));
    assert( ts != NULL );

    fct_safe_str_cpy(ts->name, name, FCT_MAX_NAME);
    ts->mode = ts_mode_cnt;
    fct_nlist__init(&(ts->test_list));
    return ts;
}



static nbool_t
fct_ts__is_more_tests(fct_ts_t const *ts)
{
    assert( ts != NULL );
    assert( !fct_ts__is_end(ts) );
    return ts->curr_test_num < ts->total_test_num;
}


/* Indicates that we have started a test case. */
static void
fct_ts__test_begin(fct_ts_t *ts)
{
    assert( !fct_ts__is_end(ts) );
    ++(ts->curr_test_num);
}


/* Takes OWNERSHIP of a test object, and warehouses it for later stat
generation. */
static void
fct_ts__add_test(fct_ts_t *ts, fct_test_t *test)
{
    assert( ts != NULL && "invalid arg");
    assert( test != NULL && "invalid arg");
    assert( !fct_ts__is_end(ts) );
    fct_nlist__append(&(ts->test_list), test);
}


static void
fct_ts__test_end(fct_ts_t *ts)
{
    assert( ts != NULL );
    assert( fct_ts__is_test_mode(ts) && "not in test mode, can't end!" );

    /* After a test has completed, move to teardown mode. */
    ts->mode = ts_mode_teardown;
}


/* Increments the internal count by 1. */
static void
fct_ts__inc_total_test_num(fct_ts_t *ts)
{
    assert( ts != NULL );
    assert( fct_ts__is_cnt_mode(ts) );
    assert( !fct_ts__is_end(ts) );
    ++(ts->total_test_num);
}


/* Flags the end of the setup, which implies we are going to move into
setup mode. You must be already in setup mode for this to work! */
static void
fct_ts__setup_end(fct_ts_t *ts)
{
    assert( fct_ts__is_setup_mode(ts) );
    assert( !fct_ts__is_end(ts) );
    ts->mode = ts_mode_test;
}


/* Flags the end of the teardown, which implies we are going to move
into setup mode (for the next 'iteration'). */
static void
fct_ts__teardown_end(fct_ts_t *ts)
{
    assert( fct_ts__is_teardown_mode(ts) );
    assert( !fct_ts__is_end(ts) );
    /* We have to decide if we should keep on testing by moving into tear down
    mode or if we have reached the real end and should be moving into the
    ending mode. */
    if ( fct_ts__is_more_tests(ts) )
    {
        ts->mode = ts_mode_setup;
    }
    else
    {
        ts->mode = ts_mode_ending;
    }
}


/* Flags the end of the counting, and proceeding to the first setup.
Consider the special case when a test suite has NO tests in it, in
that case we will have a current count that is zero, in which case
we can skip right to 'ending'. */
static void
fct_ts__cnt_end(fct_ts_t *ts)
{
    assert( ts != NULL );
    assert( fct_ts__is_cnt_mode(ts) );
    assert( !fct_ts__is_end(ts) );
    if (ts->total_test_num == 0  )
    {
        ts->mode = ts_mode_ending;
    }
    else
    {
        ts->mode = ts_mode_setup;
    }
}


static nbool_t
fct_ts__is_test_cnt(fct_ts_t const *ts, int test_num)
{
    assert( ts != NULL );
    assert( 0 <= test_num );
    assert( test_num < ts->total_test_num );
    assert( !fct_ts__is_end(ts) );

    /* As we roll through the tests we increment the count. With this
    count we can decide if we need to execute a test or not. */
    return test_num == ts->curr_test_num;
}


/* Returns the # of tests on the FCT TS object. This is the actual
# of tests executed. */
static size_t
fct_ts__tst_cnt(fct_ts_t const *ts)
{
    assert( ts != NULL );
    assert(
        fct_ts__is_end(ts)
        && "can't count number of tests executed until the test suite ends"
    );
    return fct_nlist__size(&(ts->test_list));
}


/* Returns the # of tests in the TS object that passed. */
static size_t
fct_ts__tst_cnt_passed(fct_ts_t const *ts)
{
    size_t tally =0;

    assert( ts != NULL );
    assert( fct_ts__is_end(ts) );

    FCT_NLIST_FOREACH_BGN(fct_test_t*, test, &(ts->test_list))
    {
        if ( fct_test__is_pass(test) )
        {
            tally += 1;
        }
    }
    FCT_NLIST_FOREACH_END();
    return tally;
}


/* Returns the # of checks made throughout a test suite. */
static size_t
fct_ts__chk_cnt(fct_ts_t const *ts)
{
    size_t tally =0;

    assert( ts != NULL );

    FCT_NLIST_FOREACH_BGN(fct_test_t *, test, &(ts->test_list))
    {
        tally += fct_test__chk_cnt(test);
    }
    FCT_NLIST_FOREACH_END();
    return tally;
}

/*
--------------------------------------------------------
FCT COMMAND LINE OPTION INITIALIZATION (fct_clo_init)
--------------------------------------------------------

Structure used for command line initialization. To keep it clear that we do
not delete the char*'s present on this structure.
*/


typedef enum
{
    FCT_CLO_STORE_UNDEFINED,
    FCT_CLO_STORE_TRUE,
    FCT_CLO_STORE_VALUE
} fct_clo_store_t;


typedef struct _fct_clo_init_t
{
    /* What to parse for this option. --long versus -s. */
    char const *long_opt;     /* i.e. --help */
    char const *short_opt;    /* i.e. -h */

    /* What action to take when the option is activated. */
    fct_clo_store_t action;

    /* The help string for the action. */
    char const *help;
} fct_clo_init_t;


/* Use when defining the option list. */
#define FCT_CLO_INIT_NULL  \
    {NULL, NULL, FCT_CLO_STORE_UNDEFINED, NULL}


/*
--------------------------------------------------------
FCT COMMAND LINE OPTION (fct_clo)
--------------------------------------------------------

Specifies the command line configuration options. Use this
to help initialize the fct_clp (command line parser).
*/


/* Handy strings for storing "true" and "false". We can reference
these strings throughout the parse operation and not have to
worry about dealing with memory. */
#define FCT_CLO_TRUE_STR "1"


typedef struct _fct_clo_t
{
    /* What to parse for this option. --long versus -s. */
    char *long_opt;     /* i.e. --help */
    char *short_opt;    /* i.e. -h */

    /* What action to take when the option is activated. */
    fct_clo_store_t action;

    /* The help string for the action. */
    char *help;

    /* The result. */
    char *value;
} fct_clo_t;


#define fct_clo_new()  ((fct_clo_t*)calloc(1, sizeof(fct_clo_t)))


static void
fct_clo__del(fct_clo_t *clo)
{
    if ( clo == NULL )
    {
        return;
    }
    if ( clo->long_opt )
    {
        free(clo->long_opt);
    }
    if ( clo->short_opt)
    {
        free(clo->short_opt);
    }
    if ( clo->value )
    {
        free(clo->value);
    }
    if ( clo->help )
    {
        free(clo->help);
    }
    free(clo);
}


static fct_clo_t*
fct_clo_new2(fct_clo_init_t const *clo_init)
{
    fct_clo_t *clone = NULL;
    int ok =0;
    clone = fct_clo_new();
    if ( clone == NULL )
    {
        return NULL;
    }
    clone->action = clo_init->action;
    if ( clo_init->help == NULL )
    {
        clone->help = NULL;
    }
    else
    {
        clone->help = fct_str_clone(clo_init->help);
        if ( clone->help == NULL )
        {
            ok =0;
            goto finally;
        }
    }
    if ( clo_init->long_opt == NULL )
    {
        clone->long_opt = NULL;
    }
    else
    {
        clone->long_opt = fct_str_clone(clo_init->long_opt);
        if ( clone->long_opt == NULL )
        {
            ok = 0;
            goto finally;
        }
    }
    if ( clo_init->short_opt == NULL )
    {
        clone->short_opt = NULL;
    }
    else
    {
        clone->short_opt = fct_str_clone(clo_init->short_opt);
        if ( clone->short_opt == NULL )
        {
            ok =0;
            goto finally;
        }
    }
    ok = 1;
finally:
    if ( !ok )
    {
        fct_clo__del(clone);
        clone = NULL;
    }
    return clone;
}


static int
fct_clo__is_option(fct_clo_t const *clo, char const *option)
{
    assert( option != NULL);
    assert( clo != NULL );
    return ((clo->long_opt != NULL
             && _fct_str_equal(clo->long_opt, option, _fct_check_char))
            ||
            (clo->short_opt != NULL
             && _fct_str_equal(clo->short_opt, option, _fct_check_char))
           );
}


#define fct_clo__set_value(_CLO_, _VAL_) \
    (_CLO_)->value = fct_str_clone((_VAL_));

/*
--------------------------------------------------------
FCT COMMAND PARSER (fct_clp)
--------------------------------------------------------
*/

#define FCT_CLP_MAX_ERR_MSG_LEN     256

typedef struct _fct_clp_t
{
    /* List of command line options. */
    fct_nlist_t clo_list;

    /* List of parameters (not options). */
    fct_nlist_t param_list;

    char error_msg[FCT_CLP_MAX_ERR_MSG_LEN];
    int is_error;
} fct_clp_t;


static void
fct_clp__final(fct_clp_t *clp)
{
    fct_nlist__final(&(clp->clo_list), (fct_nlist_on_del_t)fct_clo__del);
    fct_nlist__final(&(clp->param_list), (fct_nlist_on_del_t)free);
}


/* Returns false if we ran out of memory. */
static int
fct_clp__init(fct_clp_t *clp, fct_clo_init_t const *options)
{
    fct_clo_init_t const *pclo =NULL;
    int ok =0;

    assert( clp != NULL );
    assert( options != NULL );

    /* It is just much saner to manage a clone of the options. Then we know
    who is in charge of the memory. */
    fct_nlist__init(&(clp->clo_list));
    for ( pclo = options; pclo->action != FCT_CLO_STORE_UNDEFINED; ++pclo )
    {
        fct_clo_t *cpy = fct_clo_new2(pclo);
        if ( cpy == NULL )
        {
            ok = 0;
            goto finally;
        }
        fct_nlist__append(&(clp->clo_list), (void*)cpy);
    }

    fct_nlist__init(&(clp->param_list));

    ok =1;
finally:
    if ( !ok )
    {
        fct_clp__final(clp);
    }
    return ok;
}


/* Parses the command line arguments. Use fct_clp__is_error and
fct_clp__get_error to figure out if something went awry. */
static void
fct_clp__parse(fct_clp_t *clp, int argc, char const *argv[])
{
    int argi =1;
    int is_option =0;
    char *arg =NULL;
    char *token =NULL;
    char *next_token =NULL;

    clp->error_msg[0] = '\0';
    clp->is_error =0;

    while ( argi < argc )
    {
        is_option =0;
        token =NULL;
        next_token = NULL;
        arg = fct_str_clone(argv[argi]);
#if _MSC_VER > 1300
        token = strtok_s(arg, "=", &next_token);
#else
        token = strtok(arg, "=");
        next_token = strtok(NULL, "=");
#endif

        FCT_NLIST_FOREACH_BGN(fct_clo_t*, pclo, &(clp->clo_list))
        {
            /* Need to reset for each search. strtok below is destructive. */
            if ( fct_clo__is_option(pclo, token) )
            {
                is_option =1;
                if ( pclo->action == FCT_CLO_STORE_VALUE )
                {
                    /* If this is --xxxx=value then the next strtok should succeed.
                    Otherwise, we need to chew up the next argument. */
                    if ( next_token != NULL && strlen(next_token) > 0 )
                    {
                        fct_clo__set_value(pclo, next_token);
                    }
                    else
                    {
                        ++argi; /* Chew up the next value */
                        if ( argi >= argc )
                        {
                            /* error */
                            fct_snprintf(
                                clp->error_msg,
                                FCT_CLP_MAX_ERR_MSG_LEN,
                                "missing argument for %s",
                                token
                            );
                            clp->is_error =1;
                            break;
                        }
                        fct_clo__set_value(pclo, argv[argi]);
                    }
                }
                else if (pclo->action == FCT_CLO_STORE_TRUE)
                {
                    fct_clo__set_value(pclo, FCT_CLO_TRUE_STR);
                }
                else
                {
                    assert("undefined action requested");
                }
                break;  /* No need to parse this argument further. */
            }
        }
        FCT_NLIST_FOREACH_END();

        /* If we have an error, exit. */
        if ( clp->is_error )
        {
            break;
        }

        /* If we walked through all the options, and didn't find
        anything, then we must have a parameter. Forget the fact that
        an unknown option will be treated like a parameter... */
        if ( !is_option )
        {
            fct_nlist__append(&(clp->param_list), arg);
            arg =NULL;  /* Owned by the nlist */
        }

        ++argi;

        if ( arg != NULL )
        {
            free(arg);
            arg =NULL;
        }
    }
}


static fct_clo_t const*
fct_clp__get_clo(fct_clp_t const *clp, char const *option)
{
    fct_clo_t const *found =NULL;

    FCT_NLIST_FOREACH_BGN(fct_clo_t const*, pclo, &(clp->clo_list))
    {
        if ( fct_clo__is_option(pclo, option) )
        {
            found = pclo;
            break;
        }
    }
    FCT_NLIST_FOREACH_END();
    return found;
}

#define fct_clp__optval(_CLP_, _OPTION_) \
    fct_clp__optval2((_CLP_), (_OPTION_), NULL)


/* Returns the value parsed by equal to OPTION. If the value wasn't
parsed, the DEFAULT_VAL is returned instead. */
static char const*
fct_clp__optval2(fct_clp_t *clp, char const *option, char const *default_val)
{
    fct_clo_t const *clo =NULL;
    assert( clp != NULL );
    assert( option != NULL );
    clo = fct_clp__get_clo(clp, option);
    if ( clo == NULL )
    {
        return default_val;
    }
    return clo->value;
}


/* Mainly used for unit tests. */
#define fct_clp__is_param(_CLP_, _PARAM_, _IS_PARAM_OUT_)\
    *(_IS_PARAM_OUT_) = 0;\
    FCT_NLIST_FOREACH_BGN(char *, aparam, &((_CLP_)->param_list))\
    {\
        if ( _fct_str_equal(aparam, (_PARAM_), _fct_check_char) )\
        {\
            *(_IS_PARAM_OUT_) = 1;\
            break;\
        }\
    }\
    FCT_NLIST_FOREACH_END();\
 
#define fct_clp__is_error(_CLP_) ((_CLP_)->is_error)
#define fct_clp__get_error(_CLP_) ((_CLP_)->error_msg);

#define fct_clp__num_clo(_CLP_) \
    (fct_nlist__size(&((_CLP_)->clo_list)))

#define fct_clp__param_cnt(_CLP_) \
    (fct_nlist__size(&((_CLP_)->param_list)))

/* Returns a *reference* to the parameter at _IDX_. Do not modify
its contents. */
#define fct_clp__param_at(_CLP_, _IDX_) \
    ((char const*)fct_nlist__at(&((_CLP_)->param_list), (_IDX_)))


/* Returns true if the given option was on the command line.
Use either the long or short option name to check against. */
#define fct_clp__is(_CLP_, _OPTION_) \
    (fct_clp__optval((_CLP_), (_OPTION_)) != NULL)



/*
--------------------------------------------------------
FCT NAMESPACE
--------------------------------------------------------

The macros below start to pollute the watch window with
lots of "system" variables. This NAMESPACE is an
attempt to hide all the "system" variables in one place.

At the moment it is an ad-hoc operation. There is a
blueprint to address this further in the 1.2 release.
*/

typedef struct _fct_namespace_t
{
    fct_test_t *curr_test;
} fct_namespace_t;


static void
fct_namespace_init(fct_namespace_t *ns)
{
    assert( ns != NULL && "invalid argument!");
    memset(ns, 0, sizeof(fct_namespace_t));
}


/*
--------------------------------------------------------
FCT KERNAL
--------------------------------------------------------

The "fctkern" is a singleton that is defined throughout the
system.
*/

struct _fctkern_t
{
    /* Command line parsing. */
    fct_clp_t clp;

    /* This is an list of loggers that can be used in the fct system.
    You/ can attach _MAX_LOGGERS to any framework. */
    fct_nlist_t logger_list;

    /* This is a list of prefix's that can be used to determine if a
    test is should be run or not. */
    fct_nlist_t prefix_list;

    /* This is a list of test suites that where generated throughout the
    testing process. */
    fct_nlist_t ts_list;

    /* Holds variables used throughout MACRO MAGIC. In order to reduce
    the "noise" in the watch window during a debug trace. */
    fct_namespace_t ns;
};


#define FCT_OPT_VERSION "--version"
static fct_clo_init_t FCT_CLP_OPTIONS[] =
{
    /* Totally unsafe, since we are assuming we can clean out this data,
    what I need to do is have an "initialization" object, full of
    const objects. But for now, this should work. */
    {FCT_OPT_VERSION,
        NULL,   /* No short version */
        FCT_CLO_STORE_TRUE,
        "Displays the FCTX version number and exits."},
    FCT_CLO_INIT_NULL /* Sentinel */
};


/* Returns the number of filters defined for the fct kernal. */
#define fctkern__filter_cnt(_NK_) (fct_nlist__size(&((_NK_)->prefix_list)))


static void
fctkern__add_logger(fctkern_t *nk, fct_logger_i *logger_owns)
{
    assert(nk != NULL && "invalid arg");
    assert(logger_owns != NULL && "invalid arg");
    fct_nlist__append(&(nk->logger_list), logger_owns);
}


/* Appends a prefix filter that is used to determine if a test can
be executed or not. If the test starts with the same characters as
the prefix, then it should be "runnable". The prefix filter must be
a non-NULL, non-Blank string. */
static void
fctkern__add_prefix_filter(fctkern_t *nk, char const *prefix_filter)
{
    char *filter =NULL;
    size_t filter_len =0;
    assert( nk != NULL && "invalid arg" );
    assert( prefix_filter != NULL && "invalid arg" );
    assert( strlen(prefix_filter) > 0 && "invalid arg" );
    /* First we make a copy of the prefix, then we store it away
    in our little list. */
    filter_len = strlen(prefix_filter);
    filter = (char*)malloc(sizeof(char)*(filter_len+1));
    fct_safe_str_cpy(filter, prefix_filter, filter_len+1);
    fct_nlist__append(&(nk->prefix_list), (void*)filter);
}


/* Cleans up the contents of a fctkern. NULL does nothing. */
static void
fctkern__final(fctkern_t *nk)
{
    if ( nk == NULL )
    {
        return;
    }

    fct_nlist__final(&(nk->logger_list), (fct_nlist_on_del_t)fct_logger__del);

    /* The prefix list is a list of malloc'd strings. */
    fct_nlist__final(&(nk->prefix_list), (fct_nlist_on_del_t)free);

    fct_nlist__final(&(nk->ts_list), (fct_nlist_on_del_t)fct_ts__del);
}


/* Parses the command line and sets up the framework. The argc and argv
should be directly from the program's main. */
static int
fctkern__init(fctkern_t *nk, int argc, const char *argv[])
{
    fct_logger_i *standard_logger = NULL;
    int num_params =0;
    int param_i =0;
    nbool_t ok = FCT_FALSE;

    if ( argc == 0 && argv == NULL )
    {
        return 0;
    }

    memset(nk, 0, sizeof(fctkern_t));

    fct_nlist__init(&(nk->logger_list));
    fct_nlist__init(&(nk->prefix_list));
    fct_nlist__init(&(nk->ts_list));

    /* TODO: Allow client code to extend the options. */
    fct_clp__init(&(nk->clp), FCT_CLP_OPTIONS);

    fct_clp__parse(&(nk->clp), argc, argv);
    if ( fct_clp__is_error(&(nk->clp)) )
    {
        char *err = fct_clp__get_error(&(nk->clp));
        fprintf(stderr, "error: %s", err);
        ok =0;
        goto finally;
    }

    /* TODO: This is where we can "configure" what logger to pull out. Be nice
    if we can provide some means for the client code to 'override' this
    as well as from the command prompt. */
    standard_logger = (fct_logger_i*) fct_standard_logger__new();
    if ( standard_logger == NULL )
    {
        ok = FCT_FALSE;
        goto finally;
    }

    fctkern__add_logger(nk, standard_logger);
    standard_logger = NULL;   /* Owned by the nk list. */

    /* Our basic parser. For now we just take each 'argv' and assume
    that it is a prefix filter.  */
    num_params = fct_clp__param_cnt(&(nk->clp));
    for ( param_i =0; param_i < num_params; ++param_i )
    {
        char const *param = fct_clp__param_at(&(nk->clp), param_i);
        fctkern__add_prefix_filter(nk, param);
    }

    fct_namespace_init(&(nk->ns));

    ok =1;
finally:
    if ( !ok )
    {
        fctkern__final(nk);
    }
    return ok;
}


/* Takes OWNERSHIP of the test suite after we have finished executing
its contents. This way we can build up all kinds of summaries at the end
of a run. */
static void
fctkern__add_ts(fctkern_t *nk, fct_ts_t *ts)
{
    assert( nk != NULL );
    assert( ts != NULL );
    fct_nlist__append(&(nk->ts_list), ts);
}


/* Returns FCT_TRUE if the supplied test_name passes the filters set on
this test suite. If there are no filters, we return FCT_TRUE always. */
static nbool_t
fctkern__pass_filter(fctkern_t *nk, char const *test_name)
{
    size_t prefix_i =0;
    size_t prefix_list_size =0;

    assert( nk != NULL && "invalid arg");
    assert( test_name != NULL );
    assert( strlen(test_name) > 0 );

    prefix_list_size = fctkern__filter_cnt(nk);

    /* If there is no filter list, then we return FCT_TRUE always. */
    if ( prefix_list_size == 0 )
    {
        return FCT_TRUE;
    }

    /* Iterate through the prefix filter list, and see if we have
    anything that does not pass. All we require is ONE item that
    passes the test in order for us to succeed here. */
    for ( prefix_i = 0; prefix_i != prefix_list_size; ++prefix_i )
    {
        char const *prefix = (char const*)fct_nlist__at(&(nk->prefix_list), prefix_i);
        nbool_t pass = fct_filter_pass(prefix, test_name);
        if ( pass )
        {
            return FCT_TRUE;
        }
    }

    /* Otherwise, we never managed to find a prefix that satisfied the
    supplied test name. Therefore we have failed to pass to the filter
    list test. */
    return FCT_FALSE;
}


/* Returns the number of tests that were performed. */
static size_t
fctkern__tst_cnt(fctkern_t const *nk)
{
    size_t tally =0;
    assert( nk != NULL );

    FCT_NLIST_FOREACH_BGN(fct_ts_t *, ts, &(nk->ts_list))
    {
        tally += fct_ts__tst_cnt(ts);
    }
    FCT_NLIST_FOREACH_END();
    return tally;
}


/* Returns the number of tests that passed. */
static size_t
fctkern__tst_cnt_passed(fctkern_t const *nk)
{
    size_t tally =0;
    assert( nk != NULL );

    FCT_NLIST_FOREACH_BGN(fct_ts_t*, ts, &(nk->ts_list))
    {
        tally += fct_ts__tst_cnt_passed(ts);
    }
    FCT_NLIST_FOREACH_END();

    return tally;
}


/* Returns the number of tests that failed. */
#define fctkern__tst_cnt_failed(nk) \
    (fctkern__tst_cnt(nk) - fctkern__tst_cnt_passed(nk))


/* Returns the number of checks made throughout the entire test. */
static size_t
fctkern__chk_cnt(fctkern_t const *nk)
{
    size_t tally =0;
    assert( nk != NULL );

    FCT_NLIST_FOREACH_BGN(fct_ts_t *, ts, &(nk->ts_list))
    {
        tally += fct_ts__chk_cnt(ts);
    }
    FCT_NLIST_FOREACH_END();
    return tally;
}


/* Indicates the very end of all the tests. */
#define fctkern__end(nk) /* unused */


static void
fctkern__log_suite_start(fctkern_t *nk, fct_ts_t const *ts)
{
    assert( nk != NULL );
    assert( ts != NULL );
    FCT_NLIST_FOREACH_BGN(fct_logger_i*, logger, &(nk->logger_list))
    {
        fct_logger__on_test_suite_start(logger, ts);
    }
    FCT_NLIST_FOREACH_END();
}


static void
fctkern__log_suite_end(fctkern_t *nk, fct_ts_t const *ts)
{
    assert( nk != NULL );
    assert( ts != NULL );
    FCT_NLIST_FOREACH_BGN(fct_logger_i*, logger, &(nk->logger_list))
    {
        fct_logger__on_test_suite_end(logger, ts);
    }
    FCT_NLIST_FOREACH_END();
}


/* Use this for displaying information about a "Check" (i.e.
a condition). */
static void
fctkern__log_chk(fctkern_t *nk, fctchk_t const *chk)
{
    assert( nk != NULL );
    assert( chk != NULL );

    FCT_NLIST_FOREACH_BGN(fct_logger_i*, logger, &(nk->logger_list))
    {
        fct_logger__on_cndtn(logger, chk);
    }
    FCT_NLIST_FOREACH_END();
}


/* Use this for displaying warning messages. */
static void
fctkern__log_warn(fctkern_t *nk, char const *warn)
{
    assert( nk != NULL );
    assert( warn != NULL );
    FCT_NLIST_FOREACH_BGN(fct_logger_i*, logger, &(nk->logger_list))
    {
        fct_logger__on_warn(logger, warn);
    }
    FCT_NLIST_FOREACH_END();
}


/* Called whenever a test is started. */
static void
fctkern__log_test_start(fctkern_t *nk, fct_test_t const *test)
{
    assert( nk != NULL );
    assert( test != NULL );
    FCT_NLIST_FOREACH_BGN(fct_logger_i*, logger, &(nk->logger_list))
    {
        fct_logger__on_test_start(logger, test);
    }
    FCT_NLIST_FOREACH_END();
}


static void
fctkern__log_test_end(fctkern_t *nk, fct_test_t const *test)
{
    assert( nk != NULL );
    assert( test != NULL );
    FCT_NLIST_FOREACH_BGN(fct_logger_i*, logger, &(nk->logger_list))
    {
        fct_logger__on_test_end(logger, test);
    }
    FCT_NLIST_FOREACH_END();
}


#define fctkern__log_start(_NK_) \
   {\
       FCT_NLIST_FOREACH_BGN(fct_logger_i*, logger, &((_NK_)->logger_list))\
       {\
          fct_logger__on_fct_start(logger, (_NK_));\
       }\
       FCT_NLIST_FOREACH_END();\
   }


#define fctkern__log_end(_NK_) \
    {\
       FCT_NLIST_FOREACH_BGN(fct_logger_i*, logger, &((_NK_)->logger_list))\
       {\
          fct_logger__on_fct_end(logger, (_NK_));\
       }\
       FCT_NLIST_FOREACH_END();\
    }


static int
fctkern__is_clp_opt(fctkern_t *nk, char const *opt_str)
{
    assert( opt_str != NULL );
    return opt_str[0] != '\0'
           && fct_clp__is(&(nk->clp), opt_str);
}


/*
-----------------------------------------------------------
LOGGER INTERFACE

Defines an interface to a logging system. A logger
must define the following functions in order to hook
into the logging system.

See the "Standard Logger" and "Minimal Logger" as examples
of the implementation.
-----------------------------------------------------------
*/

typedef void (*fct_logger_on_cndtn_fn)(fct_logger_i *self,
                                       fctchk_t const *chk);

typedef struct _fct_logger_i_vtable_t
{
    fct_logger_on_cndtn_fn on_cndtn;
    void (*on_test_start)(fct_logger_i *logger, fct_test_t const *test);
    void (*on_test_end)(fct_logger_i *logger, fct_test_t const *test);
    void (*on_test_suite_start)(fct_logger_i *logger, fct_ts_t const *ts);
    void (*on_test_suite_end)(fct_logger_i *logger, fct_ts_t const *ts);
    void (*on_fct_start)(fct_logger_i *logger, fctkern_t const *kern);
    void (*on_fct_end)(fct_logger_i *logger, fctkern_t const *kern);
    void (*on_delete)(fct_logger_i *logger);
    void (*on_warn)(fct_logger_i *logger, char const *msg);
} fct_logger_i_vtable_t;

#define _fct_logger_head \
    fct_logger_i_vtable_t *vtable

struct _fct_logger_i
{
    _fct_logger_head;
};


static fct_logger_i_vtable_t fct_logger_default_vtable =
{
    NULL,   /* on_cndtn */
    NULL,   /* on_test_start */
    NULL,   /* on_test_end */
    NULL,   /* on_test_suite_start */
    NULL,   /* on_test_suite_end */
    NULL,   /* on_fct_start */
    NULL,   /* on_fct_end */
    NULL,   /* on_delete */
    NULL    /* on_warn */
};


/* Initializes the elements of a logger interface so they are at their
standard values. */
static void
fct_logger__init(fct_logger_i *logger)
{
    assert( logger != NULL );
    logger->vtable = &fct_logger_default_vtable;
}


static void
fct_logger__del(fct_logger_i *logger)
{
    if ( logger == NULL )
    {
        return;
    }
    if ( logger->vtable->on_delete)
    {
        logger->vtable->on_delete(logger);
    }
}


static void
fct_logger__on_test_start(fct_logger_i *logger, fct_test_t const *test)
{
    assert( logger != NULL && "invalid arg");
    assert( test != NULL && "invalid arg");

    if ( logger->vtable->on_test_start != NULL )
    {
        logger->vtable->on_test_start(logger, test);
    }
}


static void
fct_logger__on_test_end(fct_logger_i *logger, fct_test_t const *test)
{
    assert( logger != NULL && "invalid arg");
    assert( test != NULL && "invalid arg");

    if ( logger->vtable->on_test_end != NULL )
    {
        logger->vtable->on_test_end(logger, test);
    }
}


static void
fct_logger__on_test_suite_start(fct_logger_i *logger, fct_ts_t const *ts)
{
    assert( logger != NULL && "invalid arg");
    assert( ts != NULL && "invalid arg");

    if ( logger->vtable->on_test_suite_start != NULL )
    {
        logger->vtable->on_test_suite_start(logger, ts);
    }
}


static void
fct_logger__on_test_suite_end(fct_logger_i *logger, fct_ts_t const *ts)
{
    assert( logger != NULL && "invalid arg");
    assert( ts != NULL && "invalid arg");

    if ( logger->vtable->on_test_suite_end != NULL )
    {
        logger->vtable->on_test_suite_end(logger, ts);
    }
}


static void
fct_logger__on_cndtn(fct_logger_i *logger, fctchk_t const *chk)
{
    assert( logger != NULL && "invalid arg");
    assert( chk != NULL && "invalid arg");

    if ( logger->vtable->on_cndtn )
    {
        logger->vtable->on_cndtn(logger, chk);
    }
}

/* When we start all our tests. */
#define fct_logger__on_fct_start(LOGGER, KERN) \
    {\
       if ( LOGGER->vtable->on_fct_start != NULL ) \
       {\
          LOGGER->vtable->on_fct_start(LOGGER, KERN);\
       }\
    }


/* When we have reached the end of ALL of our testing. */
#define fct_logger__on_fct_end(LOGGER, KERN) \
    {\
       if ( LOGGER->vtable->on_fct_end )\
       {\
          LOGGER->vtable->on_fct_end(LOGGER, KERN);\
       }\
    }


static void
fct_logger__on_warn(fct_logger_i *logger, char const *warn)
{
    assert( logger != NULL );
    assert( warn != NULL );
    if ( logger->vtable->on_warn )
    {
        logger->vtable->on_warn(logger, warn);
    }
}


/*
-----------------------------------------------------------
MINIMAL LOGGER
-----------------------------------------------------------

At the moment the MINIMAL LOGGER is currently disabled. Hope
to bring it back online soon. The only reason it is
disabled is that we don't currently have the ability to specify
loggers.
*/

#if defined(FCT_MINIMAL_LOGGER_DISABLED)

/* Minimal logger, reports the minimum amount of information needed
to determine "something is happening". */
struct _fct_minimal_logger_t
{
    _fct_logger_head;
};


static void
fct_minimal_logger__on_cndtn(fct_logger_i *self, fctchk_t const *chk)
{
    fct_unused(self);
    printf(fctchk__is_pass(chk) ? "." : "!");
}


static void
fct_minimal_logger__del(fct_logger_i *self)
{
    free(self);
}


static fct_logger_i_vtable_t fct_logger_minimal_vtable =
{
    fct_minimal_logger__on_cndtn,   /* on_cndtn */
    NULL,   /* on_test_start */
    NULL,   /* on_test_end */
    NULL,   /* on_test_suite_start */
    NULL,   /* on_test_suite_end */
    NULL,   /* on_fct_start */
    NULL,   /* on_fct_end */
    fct_minimal_logger__del,   /* on_delete */
    NULL    /* on_warn */
};

static fct_minimal_logger_t *
fct_minimal_logger__new(void)
{
    fct_minimal_logger_t *self = (fct_minimal_logger_t*)\
                                 calloc(1,sizeof(fct_minimal_logger_t));
    if ( self == NULL )
    {
        return NULL;
    }

    fct_logger__init((fct_logger_i*)self);
    self->vtable = &fct_logger_minimal_vtable;
    return self;
}
#endif /* FCT_MINIMAL_LOGGER_DISABLED */

/*
-----------------------------------------------------------
STANDARD LOGGER
-----------------------------------------------------------
*/

struct _fct_standard_logger_t
{
    _fct_logger_head;

    /* Start time. For now we use the low-accuracy time_t version. */
    fct_timer_t timer;

    /* A list of char*'s that needs to be cleaned up. */
    fct_nlist_t failed_cndtns_list;
};


/* When a failure occurrs, we will record the details so we can display
them when the log "finishes" up. */
static void
fct_standard_logger__on_cndtn(fct_logger_i *logger_, fctchk_t const *chk)
{
    fct_standard_logger_t *logger = (fct_standard_logger_t*)logger_;

    assert( logger != NULL );
    assert( chk != NULL );

    /* Only record failures. */
    if ( !fctchk__is_pass(chk) )
    {
        /* For now we will truncate the string to some set amount, later
        we can work out a dynamic string object. */
        char *str = (char*)malloc(sizeof(char)*FCT_MAX_LOG_LINE);
        assert( str != NULL );

        fct_snprintf(
            str,
            FCT_MAX_LOG_LINE,
            "%s(%d):\n    %s",
            fctchk__file(chk),
            fctchk__lineno(chk),
            fctchk__msg(chk)
        );

        /* Append it to the listing ... */
        fct_nlist__append(&(logger->failed_cndtns_list), (void*)str);
    }
}


static void
fct_standard_logger__on_test_start(fct_logger_i *logger_,
                                   fct_test_t const *test)
{
#define FCT_STANDARD_LOGGER_MAX_LINE 64
    char line[FCT_STANDARD_LOGGER_MAX_LINE];
    char const *test_name =NULL;
    size_t test_name_len =0;
    size_t test_name_line_len =0;
    fct_unused(logger_);

    memset(line, '.', sizeof(char)*FCT_STANDARD_LOGGER_MAX_LINE);
    test_name = fct_test__name(test);
    test_name_len = strlen(test_name);
    test_name_line_len = FCTMIN(
                             FCT_STANDARD_LOGGER_MAX_LINE-1,
                             test_name_len
                         );
    memcpy(line, test_name, sizeof(char)*test_name_line_len);
    if ( test_name_len < FCT_STANDARD_LOGGER_MAX_LINE-1)
    {
        line[test_name_len] = ' ';
        line[test_name_len] = ' ';
    }
    line[FCT_STANDARD_LOGGER_MAX_LINE-1] = '\0';
    fputs(line, stdout);
#undef FCT_STANDARD_LOGGER_MAX_LINE
}


static void
fct_standard_logger__on_test_end(fct_logger_i *logger_,
                                 fct_test_t const *test)
{
    nbool_t is_pass;
    fct_unused(logger_);

    is_pass = fct_test__is_pass(test);
    printf(" %s\n", (is_pass) ? "PASS" : "FAIL ***" );
}


static void
fct_standard_logger__on_test_suite_start(fct_logger_i *logger_,
        fct_ts_t const *ts)
{
    fct_unused(logger_);
    fct_unused(ts);
}


static void
fct_standard_logger__on_test_suite_end(fct_logger_i *logger_,
                                       fct_ts_t const *ts)
{
    fct_unused(logger_);
    fct_unused(ts);
}


static void
fct_standard_logger__on_fct_start(fct_logger_i *logger_,
                                  fctkern_t const *nk)
{
    fct_standard_logger_t *logger = (fct_standard_logger_t*)logger_;
    fct_unused(nk);
    fct_timer__start(&(logger->timer));
}


static void
fct_standard_logger__on_fct_end(fct_logger_i *logger_, fctkern_t const *nk)
{
    fct_standard_logger_t *logger = (fct_standard_logger_t*)logger_;
    nbool_t is_success =1;
    double elasped_time =0;
    size_t num_tests =0;
    size_t num_passed =0;

    fct_timer__stop(&(logger->timer));

    is_success = fct_nlist__size(&(logger->failed_cndtns_list)) ==0;

    if (  !is_success )
    {
        printf(
            "\n------------------------------------------------------------------------\n"
        );
        printf("FAILED TESTS\n\n");

        FCT_NLIST_FOREACH_BGN(char *, cndtn_str, &(logger->failed_cndtns_list))
        {
            printf("%s\n", cndtn_str);
        }
        FCT_NLIST_FOREACH_END();

        printf("\n");
    }

    printf(
        "\n------------------------------------------------------------------------\n"
    );

    num_tests = fctkern__tst_cnt(nk);
    num_passed = fctkern__tst_cnt_passed(nk);

    printf(
        "%s (%d/%d tests",
        (is_success) ? "PASSED" : "FAILED",
        num_passed,
        num_tests
    );

    elasped_time = fct_timer__duration(&(logger->timer));
    if ( elasped_time > 0.0000001 )
    {
        printf(" in %.6fs)\n", elasped_time);
    }
    else
    {
        /* Don't bother displaying the time to execute. */
        printf(")\n");
    }
}


static void
fct_standard_logger__del(fct_logger_i *logger_)
{
    fct_standard_logger_t *logger = (fct_standard_logger_t*)logger_;
    fct_nlist__final(&(logger->failed_cndtns_list), free);
    free(logger);
    logger_ =NULL;
}



static void
fct_standard_logger__warn(fct_logger_i* logger_, char const *warn)
{
    fct_unused(logger_);
    (void)printf("WARNING: %s", warn);
}


static fct_logger_i_vtable_t fct_standard_logger_vtable =
{
    fct_standard_logger__on_cndtn,              /* on_cndtn */
    fct_standard_logger__on_test_start,         /* on_test_start */
    fct_standard_logger__on_test_end,           /* on_test_end */
    fct_standard_logger__on_test_suite_start,   /* on_test_suite_start */
    fct_standard_logger__on_test_suite_end,     /* on_test_suite_end */
    fct_standard_logger__on_fct_start,          /* on_fct_start */
    fct_standard_logger__on_fct_end,            /* on_fct_end */
    fct_standard_logger__del,                   /* on_delete */
    fct_standard_logger__warn                   /* on_warn */
};


fct_standard_logger_t *
fct_standard_logger__new(void)
{
    fct_standard_logger_t *logger = (fct_standard_logger_t *)calloc(
                                        1, sizeof(fct_standard_logger_t)
                                    );
    if ( logger == NULL )
    {
        return NULL;
    }
    fct_logger__init((fct_logger_i*)logger);
    logger->vtable = &fct_standard_logger_vtable;

    fct_nlist__init(&(logger->failed_cndtns_list));
    fct_timer__init(&(logger->timer));

    return logger;
}


/*
------------------------------------------------------------
MACRO MAGIC
------------------------------------------------------------
This is where the show begins!
*/

/* This macro invokes a bunch of functions that need to be referenced in
order to avoid  a "unreferenced local function has been removed" warning. 
The logical acrobatics below try and make it appear to the compiler that 
they are needed, but at runtime, only the cheap, first call is made. */ 
#define FCT_REFERENCE_FUNCS() {\
    int a = 0 && _fct_check_char('a', 'b');\
    if ( a ) { _fct_check_char_lower('a', 'b'); }\
    if ( a ) { fctkern__is_clp_opt(NULL, ""); }\
    }


/*
_fct_check_char('a', 'b');\
_fct_check_char_lower('a', 'b');\
_fct_str_equal("a", "b", _fct_check_char);\
*/

/* This defines our start. The fctkern__ is a kernal object
that lives throughout the lifetime of our program. The
fctkern_ptr__ makes it easier to abstract out macros.  */
#define FCT_BGN() \
int \
main(int argc, const char* argv[])\
{\
   fctkern_t  fctkern__;\
   fctkern_t* fctkern_ptr__ = &fctkern__;\
   FCT_REFERENCE_FUNCS();\
   if ( !fctkern__init(fctkern_ptr__, argc, argv) ) {\
        (void)printf("FATAL ERROR: Unable to intialize FCT Kernal.");\
        exit(EXIT_FAILURE);\
   }\
   if ( fctkern__is_clp_opt(fctkern_ptr__, FCT_OPT_VERSION) ) {\
       printf("Built using FCTX version %s", FCT_VERSION_STR);\
       exit(EXIT_SUCCESS);\
   }\
 
/* Ends the test suite but returning the number failed. THe "chk_cnt" call is
made in order allow strict compilers to pass when it encounters unreferenced
functions. */
#define FCT_END()\
   {\
      size_t num_failed__ =0;\
      size_t num_run =0;\
      num_run = fctkern__chk_cnt(fctkern_ptr__);\
      num_failed__ = fctkern__tst_cnt_failed((fctkern_ptr__));\
      fctkern__log_end(fctkern_ptr__);\
      fctkern__end(fctkern_ptr__);\
      fctkern__final(fctkern_ptr__);\
      assert( !((int)num_failed__ < 0) && "or we got truncated!");\
      return (int)num_failed__;\
   }\
}

#define FCT_FIXTURE_SUITE_BGN(_NAME_) \
   {\
      fct_ts_t *ts__ = fct_ts_new( #_NAME_ );\
      if ( ts__ == NULL ) {\
        fctkern__log_warn((fctkern_ptr__), "out of memory");\
      }\
      else {\
          fctkern__log_suite_start((fctkern_ptr__), ts__);\
          for (;;)\
          {\
             int fct_test_num__ = -1;\
             _fct_cmt("Strict compiler warnings will complain in 'blank' suites.")\
             _fct_cmt("so we are going to do a 'noop' to trick them.")\
             fct_test_num__ = fct_test_num__;\
             if ( fct_ts__is_ending_mode(ts__) )\
             {\
                _fct_cmt("flag the test suite as complete.");\
                fct_ts__end(ts__);\
                break;\
             }


/*  Closes off a "Fixture" test suite. */
#define FCT_FIXTURE_SUITE_END() \
             if ( fct_ts__is_cnt_mode(ts__) )\
             {\
                fct_ts__cnt_end(ts__);\
             }\
          }\
          fctkern__add_ts((fctkern_ptr__), ts__);\
          fctkern__log_suite_end((fctkern_ptr__), ts__);\
          fct_ts__end(ts__);\
          ts__ = NULL;\
      }\
   }



#define FCT_SETUP_BGN()\
   if ( fct_ts__is_setup_mode(ts__) ) {

#define FCT_SETUP_END() \
   fct_ts__setup_end(ts__); }

#define FCT_TEARDOWN_BGN() \
   if ( fct_ts__is_teardown_mode(ts__) ) {\
 
#define FCT_TEARDOWN_END() \
   fct_ts__teardown_end(ts__); \
   continue; \
   }

/* Lets you create a test suite, where maybe you don't want a fixture. We
do it by 'stubbing' out the setup/teardown logic. */
#define FCT_SUITE_BGN(Name) \
   FCT_FIXTURE_SUITE_BGN(Name) {\
   FCT_SETUP_BGN() {_fct_cmt("stubbed"); } FCT_SETUP_END()\
   FCT_TEARDOWN_BGN() {_fct_cmt("stubbed");} FCT_TEARDOWN_END()\
 
#define FCT_SUITE_END() } FCT_FIXTURE_SUITE_END()


typedef enum
{
    FCT_TEST_END_FLAG_Default    = 0x0000,
    FCT_TEST_END_FLAG_ClearFail  = 0x0001,
} FCT_TEST_END_FLAG;


/* Depending on whether or not we are counting the tests, we will have to
first determine if the test is the "current" count. Then we have to determine
if we can pass the filter. Finally we will execute everything so that when a
check fails, we can "break" out to the end of the test. And in between all
that we do a memory check and fail a test if we can't build a fct_test
object (should be rare).

__NOFAIL variants are used for my own internal testing to help
confirm that checks/requirements are doing what are required. */
#define FCT_TEST_BGN(_NAME_) \
         {\
            char const *test_name__ = #_NAME_;\
            ++fct_test_num__;\
            if ( fct_ts__is_cnt_mode(ts__) )\
            {\
               fct_ts__inc_total_test_num(ts__);\
            }\
            else if ( fct_ts__is_test_mode(ts__) \
                      && fct_ts__is_test_cnt(ts__, fct_test_num__) )\
            {\
               int is_pass__= FCT_FALSE;\
               fct_ts__test_begin(ts__);\
               if ( fctkern__pass_filter(fctkern_ptr__,  test_name__ ) )\
               {\
                  fctkern_ptr__->ns.curr_test = fct_test_new( test_name__ );\
                  if ( fctkern_ptr__->ns.curr_test  == NULL ) {\
                    fctkern__log_warn(fctkern_ptr__, "out of memory");\
                    is_pass__ = FCT_FALSE;\
                  }\
                  else {\
                      fctkern__log_test_start(fctkern_ptr__, fctkern_ptr__->ns.curr_test);\
                      for (;;) \
                      {

#define FCT_TEST_END() \
                         break;\
                      }\
               }\
               fct_ts__add_test(ts__, fctkern_ptr__->ns.curr_test);\
               fctkern__log_test_end(fctkern_ptr__, fctkern_ptr__->ns.curr_test);\
               }\
               fct_ts__test_end(ts__);\
               continue;\
            }\
         }



/*
---------------------------------------------------------
CHECKING MACROS
----------------------------------------------------------

The chk variants will continue on while as the req variants will abort
if there is one test that fails. */


/* To support older compilers that do not have macro variable argument lists
we have to use a function. The macro manages to store away the line/file
location into a global before it runs this function, a trick I picked up from
the error handling in the APR library. The unfortunate thing is that we can
not carry forth the actual test through a "stringize" operation, but if you
wanted to do that you should use fct_chk. */

static int fct_xchk_lineno =0;
static char const *fct_xchk_file = NULL;
static fct_test_t *fct_xchk_test = NULL;
static fctkern_t *fct_xchk_kern =NULL;

static int
fct_xchk_fn(int is_pass, char const *format, ...)
{
    va_list args;
    fctchk_t *chk =NULL;

    va_start(args, format);
    chk = fctchk_new(
              is_pass,
              "<none-from-xchk>",
              fct_xchk_file,
              fct_xchk_lineno,
              format,
              args
          );
    if ( chk == NULL )
    {
        fctkern__log_warn(fct_xchk_kern, "out of memory (aborting test)");
        goto finally;
    }

    fct_test__add(fct_xchk_test, chk);
    fctkern__log_chk(fct_xchk_kern, chk);

finally:
    va_end(args);
    fct_xchk_lineno =0;
    fct_xchk_file =NULL;
    fct_xchk_test =NULL;
    fct_xchk_kern =NULL;
    return is_pass;
}

/* Call this with the following argument list:

   fct_xchk(test_condition, format_str, ...)

the bulk of this macro presets some globals to allow us to support
variable argument lists on older compilers. The idea came from the APR
libraries error checking routines. */
#define fct_xchk  fct_xchk_kern = fctkern_ptr__,\
                  fct_xchk_test = fctkern_ptr__->ns.curr_test,\
                  fct_xchk_lineno =__LINE__,\
                  fct_xchk_file=__FILE__,\
                  fct_xchk_fn

/* This checks the condition and reports the condition as a string
if it fails. */
#define fct_chk(_CNDTN_)  fct_xchk((_CNDTN_) ? 1 : 0, #_CNDTN_)

#define fct_req(_CNDTN_)  \
    if ( !(fct_xchk((_CNDTN_) ? 1 : 0, #_CNDTN_)) ) { break; }


#define fct_chk_eq_dbl(V1, V2) \
    fct_xchk(\
        ((int)(fabs((V1)-(V2)) < DBL_EPSILON)),\
        "chk_eq_dbl: %f != %f",\
        (V1),\
        (V2)\
        )


#define fct_chk_neq_dbl(V1, V2) \
    fct_xchk(\
        ((int)(fabs((V1)-(V2)) >= DBL_EPSILON)),\
        "chk_neq_dbl: %f == %f",\
        (V1),\
        (V2)\
        )


#define fct_chk_eq_str(V1, V2) \
    fct_xchk(_fct_str_equal((V1), (V2), _fct_check_char),\
          "chk_eq_str: '%s' != '%s'",\
          (V1),\
          (V2)\
          )


#define fct_chk_neq_str(V1, V2) \
    fct_xchk(!_fct_str_equal((V1), (V2), _fct_check_char),\
          "chk_neq_str: '%s' == '%s'",\
          (V1),\
          (V2)\
          )


#define fct_chk_eq_istr(V1, V2) \
    fct_xchk(_fct_str_equal((V1), (V2), _fct_check_char_lower),\
          "chk_eq_str: '%s' != '%s'",\
          (V1),\
          (V2)\
          )


#define fct_chk_neq_istr(V1, V2) \
    fct_xchk(!_fct_str_equal((V1), (V2), _fct_check_char_lower),\
          "chk_neq_str: '%s' == '%s'",\
          (V1),\
          (V2)\
          )


#define fct_chk_eq_int(V1, V2) \
    fct_xchk(\
        ((V1) == (V2)),\
        "chq_eq_int: %d != %d",\
        (V1),\
        (V2)\
        )


#define fct_chk_neq_int(V1, V2) \
    fct_xchk(\
        ((V1) != (V2)),\
        "chq_neq_int: %d == %d",\
        (V1),\
        (V2)\
        )


/*
---------------------------------------------------------
GUT CHECK MACROS
----------------------------------------------------------

The following macros are used to help check the "guts" of
the FCT, and to confirm that it all works according to spec.
*/

/* Generates a message to STDERR and exits the application with a
non-zero number. */
#define _FCT_GUTCHK(_CNDTN_) \
   if ( !(_CNDTN_) ) {\
      fprintf(stderr, "gutchk fail: '"  #_CNDTN_ "' was not true.\n");\
      exit(1);\
   }\
   else {\
      fprintf(stdout, "gutchk pass:  '" #_CNDTN_ "'\n");\
   }

/*
---------------------------------------------------------
MULTI-FILE TEST SUITE MACROS
----------------------------------------------------------

I struggled trying to figure this out in a way that was
as simple as possible. I wanted to be able to define
the test suite in one object file, then refer it within
the other one within the minimum amount of typing.

Unfortunately without resorting to some supermacro
work, I could only find a happy comprimise.

See test_multi.c for an example.
*/

/* The following macros are used in your separate object
file to define your test suite.  */

/* The BGN function has a whole bunch of useless calls
at the head in order to force 'unreferenced' functions
to be referenced. Ohh Me Oh My what a waste! */

#define FCTMF_FIXTURE_SUITE_BGN(NAME) \
	void NAME (fctkern_t *fctkern_ptr__) {\
        FCT_REFERENCE_FUNCS();\
        (void)fctkern__init(NULL, 0, NULL);\
        (void)fctkern__chk_cnt(fctkern_ptr__);\
        FCT_FIXTURE_SUITE_BGN( NAME ) {

#define FCTMF_FIXTURE_SUITE_END() \
		} FCT_FIXTURE_SUITE_END();\
	}

#define FCTMF_SUITE_BGN(NAME) \
	void NAME (fctkern_t *fctkern_ptr__) {\
        FCT_REFERENCE_FUNCS();\
        (void)fctkern__init(NULL, 0, NULL);\
        (void)fctkern__chk_cnt(fctkern_ptr__);\
        FCT_SUITE_BGN( NAME ) {
#define FCTMF_SUITE_END() \
       } FCT_SUITE_END(); \
   }


/* Deprecated, no longer required. */
#define FCTMF_SUITE_DEF(NAME)

/* Visual Studio 6, C++ compiler really has a trouble with
this trick done in FCTMF_SUITE_CALL. The following tries
to handle it so the old compiler can keep on going. */
#if defined(__cplusplus)
#if _MSC_VER > 1200
#    define FCT_EXTERN_FCTMF extern
#else
#    define FCT_EXTERN_FCTMF
#endif /* _MSC_VER > 1200 */
#else
#    define FCT_EXTERN_FCTMF extern
#endif /* __cplusplus */

/* Executes a test suite defined by FCTMF_SUITE* */
#define FCTMF_SUITE_CALL(NAME)  {\
    FCT_EXTERN_FCTMF void NAME (fctkern_t *);\
    (void) NAME (fctkern_ptr__);\
    }


/*
---------------------------------------------------------
FCT QUICK TEST API
----------------------------------------------------------
The goal of these little macros is to try and get you
up and running with a test as quick as possible.

The basic idea is that there is one test per test suite.
*/

#define FCT_QTEST_BGN(NAME) \
	FCT_SUITE_BGN(NAME) {\
		FCT_TEST_BGN(NAME) {\
 
#define FCT_QTEST_END() \
		} FCT_TEST_END();\
	} FCT_SUITE_END();

/*
---------------------------------------------------------
CLOSING STATEMENTS
----------------------------------------------------------
*/

#endif /* !FCT_INCLUDED__IMB */
