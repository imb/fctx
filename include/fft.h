/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================

File: fft.h
*/

/* Define this to remove unneeded WIN32 warnings. We will undefine this at
the end of the file. */
#if defined(WIN32) && !defined(_CRT_SECURE_NO_WARNINGS)
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define FFT_MAX_NAME           256
#define FFT_MAX_LOG_LINE       256

#define nbool_t int
#define FFT_TRUE   1
#define FFT_FALSE  0

/* Forward declarations. The following forward declarations are required because
there is a inter-relationship between certain objects that just can not be 
untwined. */
typedef struct _fft_logger_i fft_logger_i;
typedef struct _fft_standard_logger_t fft_standard_logger_t;
typedef struct _fft_minimal_logger_t fft_minimal_logger_t;
typedef struct _fftchk_t fftchk_t;
typedef struct _fft_test_t fft_test_t;
typedef struct _fft_ts_t fft_ts_t;
typedef struct _fftkern_t fftkern_t;

/* Forward declare some functions used throughout. */
static fft_standard_logger_t *
fft_standard_logger__new(void);

static void
fft_logger__del(fft_logger_i *logger);

static void
fft_logger__on_cndtn(fft_logger_i *self, fftchk_t const *chk);

static void
fft_logger__on_test_start(fft_logger_i *logger, fft_test_t const *test);

static void
fft_logger__on_test_end(fft_logger_i *logger, fft_test_t const *test);

static void
fft_logger__on_test_suite_start(fft_logger_i *logger, fft_ts_t const *ts);

static void
fft_logger__on_test_suite_end(fft_logger_i *logger, fft_ts_t const *ts);

static void
fft_logger__on_fft_start(fft_logger_i *logger, fftkern_t const *kern);

static void
fft_logger__on_fft_end(fft_logger_i *logger, fftkern_t const *kern);



/* Explicitly indicate a no-op */
#define fft_pass()    

#define fft_unused(x)   (x);

/* This is just a little trick to let me put comments inside of macros. I
really only want to bother with this when we are "unwinding" the macros
for debugging purposes.
*/
#if defined(FFT_CONF_UNWIND)
#	define _fft_cmt(string)		{char*_=string;} 
#else
#	define _fft_cmt(string)
#endif

/* To help with debugging macros as well, some primitive print statements
go a long way.
*/

/* 
-------------------------------------------------------- 
UTILITIES
-------------------------------------------------------- 
*/

/* Utility for truncated string copies. */
static void
fft_safe_str_cpy(char *dst, char const *src, size_t num)
{
   assert( dst != NULL );
   assert( src != NULL );
   assert( num > 0 );
   strncpy(dst, src, num);
   dst[num-1] = '\0';
}

/* Isolate the snprintf implemenation. */
int 
fft_snprintf(char *buffer, size_t buffer_len, char *format, ...)
{
   int count =0;
   va_list args;
   va_start(args, format);
   count =vsnprintf(buffer, buffer_len, format, args);
   va_end(args);
   return count;
}

/* A very, very simple "filter". This just compares the supplied prefix 
against the test_str, to see if they both have the same starting 
characters. If they do we return true, otherwise we return false. If the
prefix is a blank string or NULL, then it will return FFT_TRUE.*/
static nbool_t
fft_filter_pass(char const *prefix, char const *test_str)
{
   nbool_t is_match = FFT_FALSE;
   char const *prefix_p;
   char const *test_str_p;

   /* If you got nothing to test against, why test? */
   assert( test_str != NULL );

   /* When the prefix is NULL or blank, we always return FFT_TRUE. */
   if ( prefix == NULL  || prefix[0] == '\0' ) 
   { 
      return FFT_TRUE;
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
      return FFT_FALSE;
   }

   /* is_match will be set to the either FFT_TRUE if we kicked of the loop
   early because our filter ran out of characters or FFT_FALSE if we 
   encountered a mismatch before our filter ran out of characters. */
   return is_match;
}

/* Returns true if two reals are equal. */
nbool_t 
fft_real_eq(double v1, double v2)
{
   return (nbool_t)(fabs(v1 - v2) < DBL_EPSILON);
}


/* 
-------------------------------------------------------- 
GENERIC LIST
-------------------------------------------------------- 
*/

/* For now we will just keep it at a linear growth rate. */
#define FFT_LIST_GROWTH_FACTOR   2

/* Starting size for the list, to keep it simple we will start
at a reasonable size. */
#define FFT_LIST_START_SIZE      2

/* Helper macros for quickly iterating through a list. You should be able
to do something like,

  NLIST_FOREACH_BEGIN(fft_logger_i, logger, my_list)
  {
     fft_logger__on_blah(logger);
  }
  NLIST_FOREACH_END();

*/
#define NLIST_FOREACH_BEGIN(Type, Var, List)\
{\
   if ( List != NULL ) {\
      size_t item_i##Var;\
      size_t num_items##Var = nlist__size(List);\
      for( item_i##Var =0; item_i##Var != num_items##Var; ++item_i##Var )\
      {\
         Type Var = (Type) nlist__at((List), item_i##Var);

#define NLIST_FOREACH_END() }}}

/* Used to manage a list of loggers. This works mostly like
the STL vector, where the array grows as more items are 
appended. */
typedef struct _nlist_t nlist_t;
struct _nlist_t
{ 
   /* Item's are stored as pointers to void. */
   void **itm_list;
   
   /* Indicates the number of element's in the array. */
   size_t avail_itm_num;

   /* Indicates the number of actually elements in the array. */
   size_t used_itm_num;
};

static nlist_t *
nlist_new(void)
{
   nlist_t *list = calloc(1, sizeof(nlist_t));
   assert( list != NULL && "memory check");

   list->itm_list = malloc(sizeof(void*)*FFT_LIST_START_SIZE);
   assert( list->itm_list != NULL && "memory check");

   list->avail_itm_num =FFT_LIST_START_SIZE;
   list->used_itm_num =0;
   return list;
}

/* Cleans up list, and applies `on_del` to each item in the list. 
If on_del is NULL, it will not be applied. If `list` is NULL this
function does nothing. */
static void
nlist__del(nlist_t *list, void (*on_del)(void*))
{
   size_t itm_i =0;

   if ( list == NULL ) { return; }

   /* Walk through the list applying the destroy function, if it was 
   defined */
   if ( on_del != NULL )
   {
      for ( itm_i =0; itm_i != list->used_itm_num; ++itm_i )
      {
         on_del(list->itm_list[itm_i]);
      }
   }

   free(list->itm_list);
   free(list);
}


/* Returns the number of elements within the list. */
static size_t
nlist__size(nlist_t const *list)
{
   assert( list != NULL );
   return list->used_itm_num;
}


/* Returns the item at idx, asserts otherwise. */
static void*
nlist__at(nlist_t const *list, size_t idx)
{
   assert( list != NULL );
   assert( idx < list->used_itm_num );
   return list->itm_list[idx];
}


static void
nlist__append(nlist_t *list, void *itm)
{
   assert( list != NULL );
   assert( list->itm_list != NULL );
   assert( list->avail_itm_num != 0 );

   /* If we ran out of room, then the last increment should be equal to the
   available space, in this case we need to grow a little more. */
   if ( list->used_itm_num == list->avail_itm_num )
   {
      list->avail_itm_num = list->avail_itm_num*FFT_LIST_GROWTH_FACTOR;
      list->itm_list = realloc(
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

struct _fftchk_t {
   /* This string that represents the condition. */
   char cndtn[FFT_MAX_LOG_LINE];

   /* These indicate where the condition occurred. */
   char file[FFT_MAX_LOG_LINE];

   int lineno;

   nbool_t is_pass;
};

#define fftchk__is_pass(_CHK_) ((_CHK_)->is_pass)
#define fftchk__file(_CHK_)    ((_CHK_)->file)
#define fftchk__lineno(_CHK_)  ((_CHK_)->lineno)
#define fftchk__cndtn(_CHK_)   ((_CHK_)->cndtn)


static fftchk_t*
fftchk_new(char const *cndtn, char const *file, int lineno, nbool_t is_pass)
{
   fftchk_t *chk = NULL;

   assert( cndtn != NULL );
   assert( file != NULL );
   assert( lineno > 0 );
   
   chk = calloc(1, sizeof(fftchk_t));
   assert( chk != NULL && "out of memory");
   if ( chk == NULL ) { return NULL; }

   fft_safe_str_cpy(chk->cndtn, cndtn, FFT_MAX_LOG_LINE);
   fft_safe_str_cpy(chk->file, file, FFT_MAX_LOG_LINE);
   chk->lineno = lineno;

   chk->is_pass =is_pass;

   return chk;
}


/* Cleans up a "check" object. If the `chk` is NULL, this function does 
nothing. */
static void
fftchk__del(fftchk_t *chk)
{
   if ( chk == NULL ) { return; }
   free( chk );
}


/*
-----------------------------------------------------------
A TEST
-----------------------------------------------------------
A suite will have-a list of tests. Where each test will have-a
list of failed and passed checks.
*/

struct _fft_test_t {
   /* List of failed and passed "checks" (fftchk_t). 
   XXX - Might be wiser to keep these as one list? */
   nlist_t *failed_chks;
   nlist_t *passed_chks;

   /* The name of the test case. */
   char name[FFT_MAX_NAME];
};

#define fft_test__name(_TEST_) ((_TEST_)->name)

static fft_test_t*
fft_test_new(char const *name) {
   fft_test_t *test =NULL;

   test = malloc(sizeof(fft_test_t));
   assert( test != NULL && "out of memory");
   
   fft_safe_str_cpy(test->name, name, FFT_MAX_NAME);
     
   test->failed_chks = nlist_new();
   test->passed_chks = nlist_new();
   assert( test->failed_chks != NULL && "out of memory");
   assert( test->passed_chks != NULL && "out of memory");

   return test;
}


static nbool_t
fft_test__is_pass(fft_test_t const *test)
{
   assert( test != NULL );
   return nlist__size(test->failed_chks) == 0;   
}


static void
fft_test__add(fft_test_t *test, fftchk_t *chk)
{

   assert( test != NULL );
   assert( chk != NULL );

   /* XXX - Better to have one list, and let the "chk" object track 
   its state? */
   if ( fftchk__is_pass(chk) )
   {
      nlist__append(test->passed_chks, (void*)chk);
   }
   else
   {
      nlist__append(test->failed_chks, (void*)chk);
   }
}

/* Returns the number of checks made throughout the test. */
static int
fft_test__chk_cnt(fft_test_t const *test)
{
   assert( test != NULL );
   return nlist__size(test->failed_chks) + nlist__size(test->passed_chks);
}


static void
fft_test__del(fft_test_t *test)
{
   if (test == NULL ) { return; }
   nlist__del(test->passed_chks, fftchk__del);
   nlist__del(test->failed_chks, fftchk__del);
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
enum ts_mode {
   ts_mode_cnt,       // To setup when done counting.
   ts_mode_setup,       // To test when done setup.
   ts_mode_teardown,    // To ending mode, when no more tests.
   ts_mode_test,        // To tear down mode.
   ts_mode_ending,      // To ... 
   ts_mode_end          // .. The End.
};

#define fft__logger_list(ZUT) ((ZUT)->logger_list)
#define fft__prefix_list(ZUT) ((ZUT)->prefix_list)

/* Types of modes the test could be in. */
typedef enum {
   fft_test_status_SUCCESS,
   fft_test_status_FAILURE
} fft_test_status;

typedef struct _fft_ts_t fft_ts_t;
struct _fft_ts_t {
   /* For counting our 'current' test number, and the total number of 
   tests. */
   int  curr_test_num;
   int  total_test_num;

   /* Keeps track of the current state of the object while it is walking
   through its "FSM" */
   enum ts_mode mode;

   /* The name of the test suite. */
   char name[FFT_MAX_NAME];

   /* List of tests that where executed within the test suite. */
   nlist_t *test_list;
};


#define fft_ts__is_setup_mode(ts)     ((ts)->mode == ts_mode_setup)
#define fft_ts__is_teardown_mode(ts)  ((ts)->mode == ts_mode_teardown)
#define fft_ts__is_test_mode(ts)      ((ts)->mode == ts_mode_test)
#define fft_ts__is_ending_mode(ts)    ((ts)->mode == ts_mode_ending)
#define fft_ts__is_end(ts)            ((ts)->mode == ts_mode_end)
#define fft_ts__is_cnt_mode(ts)       ((ts)->mode == ts_mode_cnt)
#define fft_ts__name(ts)              ((ts)->name)


static fft_ts_t *
fft_ts_new(char const *name) {
   fft_ts_t *ts =NULL;
   ts = calloc(1, sizeof(fft_ts_t));
   assert( ts != NULL );

   fft_safe_str_cpy(ts->name, name, FFT_MAX_NAME);
   ts->mode = ts_mode_cnt;

   ts->test_list = nlist_new();
   assert( ts->test_list != NULL && "no memory");

   return ts;
}

static void
fft_ts__del(fft_ts_t *ts) {
   if ( ts == NULL ) { return; }
   free(ts);
}

/* Flag a test suite as complete. It will no longer accept any more tests. */
#define fft_ts__end(ts)               ((ts)->mode == ts_mode_end)

static nbool_t
fft_ts__is_more_tests(fft_ts_t const *ts) {
   assert( ts != NULL );
   assert( !fft_ts__is_end(ts) );
   return ts->curr_test_num < ts->total_test_num;
}


/* Indicates that we have started a test case. */
static void
fft_ts__test_begin(fft_ts_t *ts) {
   assert( !fft_ts__is_end(ts) );
   ++(ts->curr_test_num);
}

/* Takes OWNERSHIP of a test object, and warehouses it for later stat
generation. */
static void
fft_ts__add_test(fft_ts_t *ts, fft_test_t *test) {
   assert( ts != NULL && "invalid arg");
   assert( test != NULL && "invalid arg");
   assert( !fft_ts__is_end(ts) );
   nlist__append(ts->test_list, test);
}


static void
fft_ts__test_end(fft_ts_t *ts) {
   assert( ts != NULL );
   assert( fft_ts__is_test_mode(ts) && "not in test mode, can't end!" );

   /* We have to decide if we should keep on testing by moving into 
   tear down mode or if we have reached the end and should be moving
   into the ending mode. */
   if ( fft_ts__is_more_tests(ts) ) {
      ts->mode = ts_mode_teardown;
   } else {
      ts->mode = ts_mode_ending;
   }
}


/* Increments the internal count by 1. */
static void
fft_ts__inc_total_test_num(fft_ts_t *ts)
{
   assert( ts != NULL );
   assert( fft_ts__is_cnt_mode(ts) );
   assert( !fft_ts__is_end(ts) );
   ++(ts->total_test_num);
}


/* Flags the end of the setup, which implies we are going to move into
setup mode. You must be already in setup mode for this to work! */
static void
fft_ts__setup_end(fft_ts_t *ts)
{
   assert( fft_ts__is_setup_mode(ts) );
   assert( !fft_ts__is_end(ts) );
   ts->mode = ts_mode_test;
}


/* This cndtn is set when we have iterated through all the tests, and
there was nothing more to do. */
static void
fft_ts__ending(fft_ts_t *ts)
{
   // We can only go from 'test-mode' to 'end-down' mode.
   assert( fft_ts__is_test_mode(ts) );
   assert( !fft_ts__is_end(ts) );
   ts->mode = ts_mode_ending;
}


/* Flags the end of the teardown, which implies we are going to move
into setup mode (for the next 'iteration'). */
static void
fft_ts__teardown_end(fft_ts_t *ts)
{
   assert( fft_ts__is_teardown_mode(ts) );
   assert( !fft_ts__is_end(ts) );
   ts->mode = ts_mode_setup;
}


/* Flags the end of the counting, and proceeding to the first setup. 
Consider the special case when a test suite has NO tests in it, in
that case we will have a current count that is less than zero, 
in which case we can skip right to 'ending'. */
static void
fft_ts__cnt_end(fft_ts_t *ts)
{
   assert( ts != NULL );
   assert( fft_ts__is_cnt_mode(ts) );
   assert( !fft_ts__is_end(ts) );
   if (ts->total_test_num == 0  ) {
      ts->mode = ts_mode_ending;
   }
   else {
      ts->mode = ts_mode_setup;
   }
}


static nbool_t
fft_ts__is_test_cnt(fft_ts_t const *ts, int test_num)
{
   assert( ts != NULL );
   assert( 0 <= test_num );
   assert( test_num < ts->total_test_num );
   assert( !fft_ts__is_end(ts) );

   /* As we roll through the tests we increment the count. With this
   count we can decide if we need to execute a test or not. */
   return test_num == ts->curr_test_num;
}


/* Returns the # of tests on the FFT TS object. This is the actual
# of tests executed. */
static int
fft_ts__tst_cnt(fft_ts_t const *ts)
{
   assert( ts != NULL );
   assert( !fft_ts__is_end(ts) );
   return nlist__size(ts->test_list);
}

/* Returns the # of tests in the TS object that passed. */
static int
fft_ts__tst_cnt_passed(fft_ts_t const *ts)
{
   int tally =0;

   assert( ts != NULL );
   assert( !fft_ts__is_end(ts) );

   NLIST_FOREACH_BEGIN(fft_test_t*, test, ts->test_list)
   {
      if ( fft_test__is_pass(test) )
      {
         tally += 1;
      }
   }
   NLIST_FOREACH_END();
   return tally;
}


/* Returns the # of checks made throughout a test suite. */
static int
fft_ts__chk_cnt(fft_ts_t const *ts)
{
   int tally =0;

   assert( ts != NULL );
   
   NLIST_FOREACH_BEGIN(fft_test_t *, test, ts->test_list)
   {
      tally += fft_test__chk_cnt(test);
   }
   NLIST_FOREACH_END();
   return tally;
}

/* 
-------------------------------------------------------- 
FFT KERNAL
-------------------------------------------------------- 

The "fftkern" is a singleton that is defined throughout the 
system. 
*/

typedef struct _fftkern_t fftkern_t;
struct _fftkern_t
{
   /* This is an list of loggers that can be used in the fft system. 
   You/ can attach _MAX_LOGGERS to any framework. */
   nlist_t *logger_list;

   /* This is a list of prefix's that can be used to determine if a 
   test is should be run or not. */
   nlist_t *prefix_list;

   /* This is a list of test suites that where generated throughout the
   testing process. */
   nlist_t *ts_list;
};

/* Returns the number of filters defined for the fft kernal. */
#define fftkern__filter_cnt(_NK_) (nlist__size((_NK_)->prefix_list))


static void
fftkern__add_logger(fftkern_t *fft, fft_logger_i *logger_owns)
{
   assert(fft != NULL && "invalid arg");
   assert(logger_owns != NULL && "invalid arg");
   nlist__append(fft->logger_list, logger_owns);
   assert( fft->logger_list != NULL && "memory check");
}

/* Appends a prefix filter that is used to determine if a test can
be executed or not. If the test starts with the same characters as
the prefix, then it should be "runnable". The prefix filter must be
a non-NULL, non-Blank string. */
static void
fftkern__add_prefix_filter(fftkern_t const *fft, char const *prefix_filter)
{
   char *filter =NULL;
   int filter_len =0;

   assert( fft != NULL && "invalid arg" );
   assert( prefix_filter != NULL && "invalid arg" );
   assert( strlen(prefix_filter) > 0 && "invalid arg" );

   /* First we make a copy of the prefix, then we store it away
   in our little list. */
   filter_len = strlen(prefix_filter);
   filter = malloc(sizeof(char)*(filter_len+1));
   strncpy(filter, prefix_filter, filter_len);
   filter[filter_len] = '\0';

   nlist__append(fft->prefix_list, (void*)filter);
}

/* Parses the command line and sets up the framework. The argc and argv 
should be directly from the program's  main. */
static void
fftkern_init(fftkern_t *nk, int argc, char *argv[])
{
   fft_logger_i *standard_logger = NULL;
   int arg_i =0;

   assert( nk != NULL );

   memset(nk, 0, sizeof(fftkern_t));

   nk->logger_list = nlist_new();
   nk->prefix_list = nlist_new();
   nk->ts_list = nlist_new();

   /* Low-budget memory check for now. */
   assert( nk->logger_list != NULL );
   assert( nk->prefix_list != NULL );
   assert( nk->ts_list != NULL );

   standard_logger = (fft_logger_i*) fft_standard_logger__new();
   assert( standard_logger != NULL && "no memory!");

   /* TODO: create other loggers, based on command line args. */

   fftkern__add_logger(nk, standard_logger);   
   standard_logger = NULL;   /* Owned by the nk list. */

   /* Our basic parser. For now we just take each 'argv' and assume
   that it is a prefix filter. Notice we start at argument 1, since
   we don't care about the *name* of the program. */
   for ( arg_i =1; arg_i < argc; ++arg_i )
   {
      fftkern__add_prefix_filter(nk, argv[arg_i]);
   }
}


/* Takes OWNERSHIP of the test suite after we have finished executing
its contents. This way we can build up all kinds of summaries at the end
of a run. */
static void
fftkern__add_ts(fftkern_t *nk, fft_ts_t *ts) {
   assert( nk != NULL );
   assert( ts != NULL );
   nlist__append(nk->ts_list, ts);
}



/* Returns FFT_TRUE if the supplied `test_name` passes the filters set on
this test suite. If there are no filters, we return FFT_TRUE always. */
static nbool_t
fftkern__pass_filter(fftkern_t *nk, char const *test_name) {
   int prefix_i =0;
   int prefix_list_size =0;

   assert( nk != NULL && "invalid arg");
   assert( test_name != NULL );
   assert( strlen(test_name) > 0 );

   prefix_list_size = fftkern__filter_cnt(nk);
   
   /* If there is no filter list, then we return FFT_TRUE always. */
   if ( prefix_list_size == 0 ) {
      return FFT_TRUE;
   }   

   /* Iterate through the prefix filter list, and see if we have
   anything that does not pass. All we require is ONE item that
   passes the test in order for us to succeed here. */
   for ( prefix_i = 0; prefix_i != prefix_list_size; ++prefix_i ) {
      char const *prefix = (char const*)nlist__at(nk->prefix_list, prefix_i);
      nbool_t pass = fft_filter_pass(prefix, test_name);
      if ( pass ) {
         return FFT_TRUE;
      }
   }

   /* Otherwise, we never managed to find a prefix that satisfied the 
   supplied test name. Therefore we have failed to pass to the filter 
   list test. */
   return FFT_FALSE;
}


/* Returns the # of tests that were performed. */
static int
fftkern__tst_cnt(fftkern_t const *nk)
{
   int tally =0;
   assert( nk != NULL );

   NLIST_FOREACH_BEGIN(fft_ts_t *, ts, nk->ts_list)
   {
      tally += fft_ts__tst_cnt(ts);
   }
   NLIST_FOREACH_END();
   return tally;
}

/* Returns the # of tests that passed. */
static int
fftkern__tst_cnt_passed(fftkern_t const *nk)
{
   int tally =0;
   assert( nk != NULL );

   NLIST_FOREACH_BEGIN(fft_ts_t*, ts, nk->ts_list)
   {
      tally += fft_ts__tst_cnt_passed(ts);
   }
   NLIST_FOREACH_END();

   return tally;
}

/* Returns the # Of tests that failed. */
static int
fftkern__tst_cnt_failed(fftkern_t const *nk)
{
   /* Keep it simple for now and just do a little math. */
   int total =0;
   int passed =0;
   int failed =0;

   assert( nk != NULL );

   total = fftkern__tst_cnt(nk);
   passed = fftkern__tst_cnt_passed(nk);

   failed = total - passed;

   return failed;
}


/* Returns the # of checks made throughout the entire test. */
static int
fftkern__chk_cnt(fftkern_t const *nk)
{
   int tally =0;
   assert( nk != NULL );

   NLIST_FOREACH_BEGIN(fft_ts_t *, ts, nk->ts_list)
   {
      tally += fft_ts__chk_cnt(ts);
   }
   NLIST_FOREACH_END();
   return tally;
}


/* Indicates the very end of all the tests. */
static void
fftkern__end(fftkern_t *fft)
{
   fft_unused(fft);
}


/* Cleans up the contents of a fftkern. NULL does nothing. */
static void
fftkern__final(fftkern_t *fft) 
{
   if ( fft == NULL ) { return; }

   nlist__del(fft->logger_list, fft_logger__del);

   /* The prefix list is a list of malloc'd strings. */
   nlist__del(fft->prefix_list, free);

   nlist__del(fft->ts_list, fft_ts__del);
}

static void
fftkern__log_suite_start(fftkern_t *kern, fft_ts_t const *ts)
{
   assert( kern != NULL );
   assert( ts != NULL );
   NLIST_FOREACH_BEGIN(fft_logger_i*, logger, kern->logger_list)
   {
      fft_logger__on_test_suite_start(logger, ts);
   }
   NLIST_FOREACH_END();
}


static void
fftkern__log_suite_end(fftkern_t *kern, fft_ts_t const *ts)
{
   assert( kern != NULL );
   assert( ts != NULL );
   NLIST_FOREACH_BEGIN(fft_logger_i*, logger, kern->logger_list)
   {
      fft_logger__on_test_suite_end(logger, ts);
   }
   NLIST_FOREACH_END();
}


/* Called whenever a check is made in a test. The `cndtn` is the test in string format,
it must not be NULL. The `file` and `lineno` parameters correspond to the 
__FILE__ and __LINE__ pre-processor macros. */
static void
fftkern__log_chk(fftkern_t *kern, fftchk_t const *chk)
{
   assert( kern != NULL );
   assert( chk != NULL );
  
   NLIST_FOREACH_BEGIN(fft_logger_i*, logger, kern->logger_list)
   {
      fft_logger__on_cndtn(logger, chk);
   }
   NLIST_FOREACH_END();
}


/* Called whenever a test is started. */
static void
fftkern__log_test_start(fftkern_t *kern, fft_test_t const *test)
{
   assert( kern != NULL );
   assert( test != NULL );
   NLIST_FOREACH_BEGIN(fft_logger_i*, logger, kern->logger_list)
   {
      fft_logger__on_test_start(logger, test);
   }
   NLIST_FOREACH_END();
}


static void
fftkern__log_test_end(fftkern_t *kern, fft_test_t const *test)
{
   assert( kern != NULL );
   assert( test != NULL );
   NLIST_FOREACH_BEGIN(fft_logger_i*, logger, kern->logger_list)
   {
      fft_logger__on_test_end(logger, test);
   }
   NLIST_FOREACH_END();
}


static void
fftkern__log_start(fftkern_t *kern)
{
   assert( kern != NULL );
   NLIST_FOREACH_BEGIN(fft_logger_i*, logger, kern->logger_list)
   {
      fft_logger__on_fft_start(logger, kern);
   }
   NLIST_FOREACH_END();
}

static void
fftkern__log_end(fftkern_t *kern)
{
   assert( kern != NULL );
   NLIST_FOREACH_BEGIN(fft_logger_i*, logger, kern->logger_list)
   {
      fft_logger__on_fft_end(logger, kern);
   }
   NLIST_FOREACH_END();
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

typedef void (*fft_logger_on_cndtn_fn)(fft_logger_i *self, 
                                       fftchk_t const *chk);
#define _fft_logger_head \
   fft_logger_on_cndtn_fn on_cndtn;\
   void (*on_test_start)(fft_logger_i *logger, fft_test_t const *test);\
   void (*on_test_end)(fft_logger_i *logger, fft_test_t const *test);\
   void (*on_test_suite_start)(fft_logger_i *logger, fft_ts_t const *ts);\
   void (*on_test_suite_end)(fft_logger_i *logger, fft_ts_t const *ts);\
   void (*on_fft_start)(fft_logger_i *logger, fftkern_t const *kern);\
   void (*on_fft_end)(fft_logger_i *logger, fftkern_t const *kern);\
   void (*on_delete)(fft_logger_i *logger)\

struct _fft_logger_i {
   _fft_logger_head;
};


/* Initializes the elements of a logger interface so they are at their 
standard values. */
static void
fft_logger__init(fft_logger_i *logger)
{
   assert( logger != NULL );
   logger->on_cndtn =NULL;
   logger->on_test_start =NULL;
   logger->on_test_end =NULL;
   logger->on_test_suite_start =NULL;
   logger->on_test_suite_end =NULL;
   logger->on_fft_start =NULL;
   logger->on_fft_end =NULL;
   logger->on_delete =NULL;
}


static void
fft_logger__del(fft_logger_i *logger)
{
   if ( logger == NULL ) { return; }
   if ( logger->on_delete) { logger->on_delete(logger); }
}


static void
fft_logger__on_test_start(fft_logger_i *logger, fft_test_t const *test)
{
   assert( logger != NULL && "invalid arg");
   assert( test != NULL && "invalid arg");

   if ( logger->on_test_start != NULL )
   {
      logger->on_test_start(logger, test);
   }
}


static void
fft_logger__on_test_end(fft_logger_i *logger, fft_test_t const *test)
{
   assert( logger != NULL && "invalid arg");
   assert( test != NULL && "invalid arg");

   if ( logger->on_test_end != NULL )
   {
      logger->on_test_end(logger, test);
   }
}


static void
fft_logger__on_test_suite_start(fft_logger_i *logger, fft_ts_t const *ts)
{
   assert( logger != NULL && "invalid arg");
   assert( ts != NULL && "invalid arg");

   if ( logger->on_test_suite_start != NULL )
   {
      logger->on_test_suite_start(logger, ts);
   }
}


static void
fft_logger__on_test_suite_end(fft_logger_i *logger, fft_ts_t const *ts)
{
   assert( logger != NULL && "invalid arg");
   assert( ts != NULL && "invalid arg");

   if ( logger->on_test_suite_end != NULL )
   {
      logger->on_test_suite_end(logger, ts);
   }
}

static void
fft_logger__on_cndtn(fft_logger_i *logger, fftchk_t const *chk)
{
   assert( logger != NULL && "invalid arg");
   assert( chk != NULL && "invalid arg");

   if ( logger->on_cndtn ) 
   {
      logger->on_cndtn(logger, chk);
   }
}                        


/* When we start all our tests. */
static void
fft_logger__on_fft_start(fft_logger_i *logger, fftkern_t const *kern)
{
   assert( logger != NULL );
   assert( kern != NULL );

   if ( logger->on_fft_start != NULL ) 
   {
      logger->on_fft_start(logger, kern);
   }
}


/* When we have reached the end of ALL of our testing. */
static void
fft_logger__on_fft_end(fft_logger_i *logger, fftkern_t const *kern)
{
   assert( logger != NULL );
   assert( kern != NULL );

   if ( logger->on_fft_end )
   {
      logger->on_fft_end(logger, kern);
   }
}



/*
-----------------------------------------------------------
MINIMAL LOGGER
-----------------------------------------------------------
*/

/* Minimal logger, reports the minimum amount of information needed
to determine "something is happening". */
struct _fft_minimal_logger_t {
   _fft_logger_head;
};


static void 
fft_minimal_logger__on_cndtn(fft_logger_i *self, fftchk_t const *chk)
{
   fft_unused(self);   
   printf(fftchk__is_pass(chk) ? "." : "!");
}


static void
fft_minimal_logger__del(fft_logger_i *self)
{
   free(self);
}


static fft_minimal_logger_t *
fft_minimal_logger__new(void)
{
   fft_minimal_logger_t *self = calloc(1,sizeof(fft_minimal_logger_t));
   if ( self == NULL ) { return NULL; }

   fft_logger__init((fft_logger_i*)self);

   self->on_cndtn = fft_minimal_logger__on_cndtn;
   self->on_delete = fft_minimal_logger__del;
   return self;
}


/*
-----------------------------------------------------------
STANDARD LOGGER
-----------------------------------------------------------
*/

typedef struct _fft_standard_logger_t fft_standard_logger_t;
struct _fft_standard_logger_t {
   _fft_logger_head;

   /* Start time. For now we use the low-accuracy time_t version. */
   time_t start_time;

   /* A list of char*'s that needs to be cleaned up. */
   nlist_t *failed_cndtns_list;
};

/* When a failure occurrs, we will record the details so we can display
them when the log "finishes" up. */
static void
fft_standard_logger__on_cndtn(fft_logger_i *logger_, fftchk_t const *chk)
{
   fft_standard_logger_t *logger = (fft_standard_logger_t*)logger_;
   
   assert( logger != NULL );
   assert( chk != NULL );

   /* Only record failures. */
   if ( !fftchk__is_pass(chk) )
   {
      /* For now we will truncate the string to some set amount, later
      we can work out a dynamic string object. */
      char *str = malloc(sizeof(char)*FFT_MAX_LOG_LINE);
      assert( str != NULL );
      
      fft_snprintf(
         str, 
         FFT_MAX_LOG_LINE, 
         "%s(%d): %s", 
         fftchk__file(chk),
         fftchk__lineno(chk),
         fftchk__cndtn(chk)
         );

      /* Append it to the listing ... */
      nlist__append(logger->failed_cndtns_list, (void*)str);
   }  
}


static void
fft_standard_logger__on_test_start(fft_logger_i *logger_, 
                                   fft_test_t const *test)
{
   fft_unused(logger_);
   printf("%s ... ", fft_test__name(test));
}

static void
fft_standard_logger__on_test_end(fft_logger_i *logger_, 
                                   fft_test_t const *test)
{
   nbool_t is_pass;
   fft_unused(logger_);

   is_pass = fft_test__is_pass(test);

   printf("%s\n", (is_pass) ? "PASS" : "FAIL" );
}





static void
fft_standard_logger__on_test_suite_start(fft_logger_i *logger_, 
                                         fft_ts_t const *ts)
{
   fft_unused(logger_);
   fft_unused(ts);
}


static void
fft_standard_logger__on_test_suite_end(fft_logger_i *logger_, 
                                         fft_ts_t const *ts)
{
   fft_unused(logger_);
   fft_unused(ts);
}

static void
fft_standard_logger__on_fft_start(fft_logger_i *logger_, 
                                  fftkern_t const *nk)
{
   fft_standard_logger_t *logger = (fft_standard_logger_t*)logger_;
   fft_unused(nk);
   logger->start_time = time(&(logger->start_time));
}


static void
fft_standard_logger__on_fft_end(fft_logger_i *logger_, fftkern_t const *nk)
{
   fft_standard_logger_t *logger = (fft_standard_logger_t*)logger_;
   nbool_t is_success =1;
   time_t end_time =0;
   time_t elasped_time =0;
   int num_tests =0;
   int num_passed =0;

   end_time = time(&end_time);
   
   is_success = nlist__size(logger->failed_cndtns_list) ==0;

   if (  !is_success )
   {
      printf("\n--------------------------------------------------------\n");
      printf("FAILED TESTS\n\n");

      NLIST_FOREACH_BEGIN(char *, cndtn_str, logger->failed_cndtns_list)
      {
         printf("%s\n", cndtn_str);
      }
      NLIST_FOREACH_END();

      printf("\n");
   }

   printf("\n--------------------------------------------------------\n");

   num_tests = fftkern__tst_cnt(nk);
   num_passed = fftkern__tst_cnt_passed(nk);
   
   elasped_time = end_time - logger->start_time;

   printf(
      "TESTING %s (%d/%d tests in %d second(s))", 
      (is_success) ? "PASSED" : "FAILED",
      num_passed,
      num_tests,
      elasped_time
      );
}

static void
fft_standard_logger__del(fft_logger_i *logger_)
{
   fft_standard_logger_t *logger = (fft_standard_logger_t*)logger_;

   NLIST_FOREACH_BEGIN(char *, cndtn_str, logger->failed_cndtns_list)
   {
      free(cndtn_str);
   }
   NLIST_FOREACH_END();

   free(logger);
   logger_ =NULL;
}

fft_standard_logger_t *
fft_standard_logger__new(void)
{
   fft_standard_logger_t *logger = calloc(1, sizeof(fft_standard_logger_t));
   if ( logger == NULL ) 
   { 
      return NULL; 
   }
   fft_logger__init((fft_logger_i*)logger);
   logger->on_cndtn = fft_standard_logger__on_cndtn;
   logger->on_test_start = fft_standard_logger__on_test_start;
   logger->on_test_end = fft_standard_logger__on_test_end;
   logger->on_test_suite_start = fft_standard_logger__on_test_suite_start;
   logger->on_test_suite_end = fft_standard_logger__on_test_suite_end;
   logger->on_fft_start = fft_standard_logger__on_fft_start;
   logger->on_fft_end = fft_standard_logger__on_fft_end;
   logger->on_delete = fft_standard_logger__del;

   logger->failed_cndtns_list = nlist_new();
   assert( logger->failed_cndtns_list != NULL );

   return logger;
}



/*
------------------------------------------------------------
MAGIC MACROS
------------------------------------------------------------
*/

#define FFT_BEGIN() \
int \
main(int argc, char *argv[])\
{\
   fftkern_t fftkern__;\
   fftkern_init(&fftkern__, argc, argv);\
   fftkern__log_start(&fftkern__);


#define FFT_END()\
   {\
      int num_failed__ =0;\
      num_failed__ = fftkern__tst_cnt_failed((&fftkern__));\
      fftkern__log_end(&fftkern__);\
      fftkern__end(&fftkern__);\
      fftkern__final(&fftkern__);\
      return num_failed__;\
   }\
}

#define FFT_FIXTURE_SUITE_BEGIN(_NAME_) \
   {\
      fft_ts_t *ts__ = fft_ts_new( #_NAME_ );\
      fftkern__log_suite_start((&fftkern__), ts__);\
      for (;;)\
      {\
         int fft_test_num__ = -1;\
         _fft_cmt("Strict compiler warnings will complain in 'blank' suites.")\
         _fft_cmt("so we are going to do a 'noop' to trick them.")\
         fft_test_num__ = fft_test_num__;\
         if ( fft_ts__is_ending_mode(ts__) )\
         {\
            _fft_cmt("flag the test suite as complete.");\
            fft_ts__end(ts__);\
            break;\
         }


/*  Closes off a "Fixture" test suite. */
#define FFT_FIXTURE_SUITE_END() \
         if ( fft_ts__is_cnt_mode(ts__) )\
         {\
            fft_ts__cnt_end(ts__);\
         }\
      }\
      fftkern__add_ts((&fftkern__), ts__);\
      fftkern__log_suite_end((&fftkern__), ts__);\
      ts__ = NULL;\
   }



#define FFT_SETUP_BEGIN()\
   if ( fft_ts__is_setup_mode(ts__) ) {

#define FFT_SETUP_END() \
   fft_ts__setup_end(ts__); }

#define FFT_TEARDOWN_BEGIN() \
   if ( fft_ts__is_teardown_mode(ts__) ) {\

#define FFT_TEARDOWN_END() \
   fft_ts__teardown_end(ts__); \
   continue; \
   }

/* Lets you create a test suite, where maybe you don't want a fixture. We
do it by 'stubbing' out the setup/teardown logic. */
#define FFT_SUITE_BEGIN(Name) \
   FFT_FIXTURE_SUITE_BEGIN(Name) {\
   FFT_SETUP_BEGIN() {_fft_cmt("stubbed"); } FFT_SETUP_END()\
   FFT_TEARDOWN_BEGIN() {_fft_cmt("stubbed");} FFT_TEARDOWN_END()\

#define FFT_SUITE_END() } FFT_FIXTURE_SUITE_END()

/* A depending on whether or not we are counting the tests, we will have to 
first determine if the test is the "current" count. Then we have to determine
if we can pass the filter. Finally we will execute everything so that when a 
check fails, we can "break" out to the end of the test. */
#define FFT_TEST_BEGIN(_NAME_) \
         {\
            char const *test_name__ = #_NAME_;\
            ++fft_test_num__;\
            if ( fft_ts__is_cnt_mode(ts__) )\
            {\
               fft_ts__inc_total_test_num(ts__);\
            }\
            else if ( fft_ts__is_test_mode(ts__) \
                      && fft_ts__is_test_cnt(ts__, fft_test_num__) )\
            {\
               int is_pass__;\
               is_pass__ = FFT_FALSE;\
               fft_ts__test_begin(ts__);\
               if ( fftkern__pass_filter(&fftkern__,  test_name__ ) )\
               {\
                  fft_test_t *test__ = fft_test_new( test_name__ );\
                  fftkern__log_test_start(&fftkern__, test__);\
                  for (;;) \
                  {

#define FFT_TEST_END() \
                     break;\
                  }\
               fft_ts__add_test(ts__, test__);\
               fftkern__log_test_end(&fftkern__, test__);\
               }\
               fft_ts__test_end(ts__);\
               continue;\
            }\
         }


/*
---------------------------------------------------------
CHECKING MACROS
---------------------------------------------------------- 
*/

#define fft_chk(_CNDTN_) \
   {\
      fftchk_t *chk =NULL;\
      is_pass__ = (_CNDTN_);\
      chk = fftchk_new(#_CNDTN_, __FILE__, __LINE__, is_pass__);\
      fft_test__add(test__, chk);\
      fftkern__log_chk(&fftkern__, chk);\
      if ( !is_pass__ ) { break; }\
   }


/*
---------------------------------------------------------
GUT CHECK MACROS
---------------------------------------------------------- 

The following macros are used to help check the "guts" of
the Nut, and to confirm that it all works according to spec.
*/

/* Generates a message to STDERR and exits the application with a 
non-zero number. */
#define _FFT_GUTCHK(_CNDTN_) \
   if ( !(_CNDTN_) ) {\
      fprintf(stderr, "gutchk fail: '"  #_CNDTN_ "' was not true.\n");\
      exit(1);\
   }\
   else {\
      fprintf(stdout, "gutchk pass:  '" #_CNDTN_ "'\n");\
   }
      

/* This is defined at the start of the file. We are undefining it
here so it doesn't conflict with existing. */
#if defined(WIN32)
#   undef _CRT_SECURE_NO_WARNINGS
#endif


