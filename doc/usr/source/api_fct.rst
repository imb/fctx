========
FCTX API
========

.. module:: FCT
   :platform: Unix, Windows
   :synopsis: Framework, test suites, tests and checks.


Initialize/Finalize
-------------------

.. cfunction:: FCT_BGN()

	Initializes your test framework. Every test program needs to begin with
	this declaration.

.. cfunction:: FCT_END()

	Finalizes your test framwork. Every test program neesd to end with this
	declaration.

.. cfunction:: FCT_EXPECTED_FAILURES(num_failed)

        *New in 1.2*. Mainly used internally by FCTX to test that failures are
        occurring properly. If the actual number of failed tests matches the
        expected *num_failed*, this macro will cause the program to return 0
        instead of a non-zero value.

Test Suites
-----------

.. cfunction:: FCT_FIXTURE_SUITE_BGN(name)
	
	Following the xtest convention, every test suite needs to start with a 
	SUITE_BGN function. In by using the FIXTURE variants you are indicating
	that you wish to install a SETUP and TEARDOWN fixture via the
	:cfunc:`FCT_SETUP_BGN`/:cfunc:`FCT_SETUP_END` and
	:cfunc:`FCT_TEARDOWN_BGN`/:cfunc:`FCT_TEARDOWN_END` functions.

	See also :cfunc:`FCT_SUITE_BGN`.

        The following example shows calling a setup/teardown to allocate memory
	to *data* structure. 

	.. code-block:: c
     
	       { 
		 void *data =NULL;
		 FCT_FIXTURE_SUITE_BGN("1Suite") 
		 {
		       FCT_SETUP_BGN() 
		       {
			  data = malloc(sizeof(10));
		       }
		       FCT_SETUP_END();
		    
		       FCT_TEARDOWN_BGN()
		       {
			  free(data);
			  data =NULL;
		       }
		       FCT_TEARDOWN_END();

		       FCT_TEST_BGN("1Test")
		       {
			  fct_chk( strcmp("a", "b") != 0 );
		       }
		       FCT_TEST_END();

		 } 
		 FCT_FIXTURE_SUITE_END();
	       }

.. /*  (Just fixes VIM highlighter)


.. cfunction:: FCT_FIXTURE_SUITE_END()

	This closes a test suite that contains fixtures. If you do not wish to
	specify a setup/teardown you would use the :cfunc:`FCT_SUITE_END` 
	function instead.

.. cfunction:: FCT_SUITE_BGN(name)

        Use this FCT_SUITE variant if you do not want to bother specifying a
        SETUP and TEARDOWN blocks.

        See also :cfunc:`FCT_FIXTURE_SUITE_BGN`.

        The following test suite does not have a setup/teardown method. This
        is generally used for convenience, to group a set of tests under
        one heading (a "suite").

	.. code-block:: c
     
		 FCT_SUITE_BGN("1Suite") 
		 {
		       FCT_TEST_BGN("1Test")
		       {
			  fct_chk( strcmp("a", "b") != 0 );
		       }
		       FCT_TEST_END();
		 } 
		 FCT_SUITE_END();
	       }


.. cfunction:: FCT_SUITE_END()

        Closes the FCT_SUITE_BGN macro.

.. cfunction:: FCT_SETUP_BGN()

        Opens a SETUP block. This block is executed *before* every test.

.. cfunction:: FCT_SETUP_END()
   
        Closes the SETUP block.

.. cfunction:: FCT_TEARDOWN_BGN()

        Opens up a teardown block. This block is executed *after* every test.

.. cfunction:: FCT_TEARDOWN_END()

        Ends a teardown block. 

Conditional Test Suites
-----------------------

*New in FCTX 1.2*. The following macros provide you with the ability to run a
test suite based on some condition. If the condition is TRUE (non-zero) then
the test suite and its tests will be executed.

.. cfunction:: FCT_FIXTURE_SUITE_BGN_IF(condition, name)

        Same as :cfunc:`FCT_SUITE_BGN`, but will only run if the *condition* is
        a non-zero value (TRUE).
	
.. cfunction:: FCT_FIXTURE_SUITE_END_IF()

        Closes the :cfunc:`FCT_FIXTURE_SUITE_BGN_IF` macro.


.. cfunction:: FCT_SUITE_BGN_IF(condition, name)

        Same as :cfunc:`FCT_SUITE_BGN`, but will only run if the *condition* is
        a non-zero value (TRUE).

.. cfunction:: FCT_SUITE_END_IF()

        Closes the :cfunc:`FCT_SUITE_BGN_IF` macro.

Quick Test
----------

*New in FCTX 1.1*. This allows you to write tests without any Test Suite
infrastructure. For example,

.. code-block:: c

  /* First include the fct framework. */
  #include "fct.h"

  /* Include your API. In this case we are going to test strcmp. */
  #include <string.h>

  /* Now lets define our testing scope. */
  FCT_BGN()
  {
    /* An actual test case in the test suite. */
    FCT_QTEST_BGN(strcmp_eq)
    {
       fct_chk(strcmp("durka", "durka") == 0);
    }
    FCT_QTEST_END();


    FCT_QTEST_BGN(chk_neq)
    {
       fct_chk(strcmp("daka", "durka") !=0 );
    }
    FCT_TEST_END();

  /* Every FCT scope has an end. */
  }
  FCT_END();

.. ***

The above code block lacks any test suites, and provide a convenient way to get
of the ground quickly and start writing tests.

.. cfunction:: FCT_QTEST_BGN(name)

   Opens the quick test block with the given *name*.

.. cfunction:: FCT_QTEST_END()

   Ends the quick test block.

.. cfunction:: FCT_QTEST_BGN_IF(condition, name)

   *New in FCTX 1.2*. Opens the quick test block with the given *name*. The
   contents of the test block are only executed if the *condition* is a
   non-zero (TRUE) value.

.. cfunction:: FCT_QTEST_END_IF()

   *New in FCTX 1.2*. Ends the conditional quick test block.


Tests
-----

These define a beginning and end of a test block. See also
:cfunc:`FCT_QTEST_BGN` and :cfunc:`FCT_QTEST_END`.

.. cfunction:: FCT_TEST_BGN(name)

   Opens a test block with the given *name*.

.. cfunction:: FCT_TEST_END()

   Closes a test block. 

Conditional Tests
-----------------

*New in FCTX 1.2*.  Use these variants to run a test based on a conditional
value.

.. cfunction:: FCT_TEST_BGN_IF(condition, name)

   Opens a test block with the given *name*. The test is only executed if the
   *condition* is a non-zero (TRUE) value.

.. cfunction:: FCT_TEST_END_IF()

   Closes a test block. 


Checks
------

These are used to verify that a condition is true. They are executed within
:cfunc:`FCT_TEST_BGN`/:cfunc:`FCT_TEST_END` blocks. 


.. cfunction:: fct_chk(condition)

    Evaluates the *condition*, and if it is false will cause the tests to fail.
    Further lines in the test block continue to execute. If you want a check to
    terminate testing, then use the :cfunc:`fct_req` function instead.

    A feature of this check is that you can provide notes to yourself as in,

    .. code-block:: c

        fct_chk( it_works() && "The whoosley wazzle didn't work!");
        fct_chk(!"TODO: Write tests to confirm that the ish can wish for fish.");

    in both those cases if an error was generated (the second case always will
    fail), you will get a message in the final error log.

.. cfunction:: fct_chk_eq_dbl(a, b) 

    *New in FCTX 1.1*. Causes a test failure if *a* != *b*. Testing for
    equality is done based on an absolute floating point difference less than
    the *DBL_EPISLON* defined in the standard <float.h> file.

.. cfunction:: fct_chk_eq_int(a, b)

    *New in FCTX 1.1*. Causes a test failure if *a* != *b*. Testing for
    equality is done based on the "==" operator. An error message is generated
    showing the values of *a* and *b*.

.. cfunction:: fct_chk_eq_istr(a, b)

    *New in FCTX 1.1*. Causes a test failure if *a* != *b* (case-insensitive).
    Testing for equality is done based on first checking for NULL values, then
    making a case-insensitive compare.

.. cfunction:: fct_chk_eq_str(a, b)

    *New in FCTX 1.1*. Causes a test failure if *a* != *b*. Testing for
    equality is done based on first checking for NULL values, then making a
    case-sensitive compare.

.. cfunction:: fct_chk_incl_str(s, check) 

    *New in FCTX 1.3*. Causes a test failure when it can not find *check*
    within the given string, *s*. NULL is treated as a blank string in
    this case, thus if *check* is NULL, all *str* will pass. Down in the
    guts of this function, there is a call to the Standard C *strstr*
    function.

.. cfunction:: fct_chk_incl_istr(s, check) 

    *New in FCTX 1.3*. This is a case insensitive variant of
    :cfunc:`fct_chk_incl_str`.

.. cfunction:: fct_chk_neq_dbl(a, b) 

    *New in FCTX 1.1*. Causes a test failure if *a* == *b*. Testing for
    inequality is done based on an absolute floating point difference that is
    NOT less than the *DBL_EPISLON* defined in the standard <float.h> file. 

.. cfunction:: fct_chk_neq_int(a, b)

    *New in FCTX 1.1*. Causes a test failure if *a* == *b*. Testing for
    equality is done based on the "!=" operator. An error message is generated
    showing the values of *a* and *b*.

.. cfunction:: fct_chk_neq_istr(a, b)

    *New in FCTX 1.1*. Causes a test failure if *a* == *b* (case-insensitive).
    Testing for inequality is done based on first checking for NULL, then
    making a case-insensitive compare.

.. cfunction:: fct_chk_neq_str(a, b)

    *New in FCTX 1.1*. Causes a test failure if *a* == *b*. Testing for
    inequality is done based on first checking for NULL, then making a
    case-sensitive compare.

.. cfunction:: fct_xchk(condition, format_str, ...)

    *New in FCTX 1.1*. Evaluates the *condition*, and if it is false will cause
    the tests to fail.  Further lines in the test block continue to execute.
    The message reported is a function of a printf-style *format_str*, with
    multiple arguments.

    :cfunc:`fct_xchk` can be extended to generate your own check functions. For
    example, say you had a structure such as,

    .. code-block:: c

       typedef struct _point_t {
          float x, y, z;
       } point_t;

    you could define a macro that checks if two points are equal based on some
    epsilon value. Something that looked like this should work,

    .. code-block:: c

        #define point_is_eq(p1, p2, ep) \
            ((int)(fabs(p1.x - p2.x) < ep)) &&\
            ((int)(fabs(p1.y - p2.y) < ep)) &&\
            ((int)(fabs(p1.z - p2.z) < ep))

        #define point_chk_eq(p1, p2, ep) \
            fct_xchk(\
                point_is_eq(p1, p2, ep), \
                "failed point_is_equal:\n<Point x=%f y=%f z=%f>"\
                " !=\n<Point x=%f y=%f z=%f>",\
                p1.x, p1.y, p1.z, p2.x, p2.y, p2.z\
                );

    now your test case can utilize this to test if two points are equal, and
    you will get a meaningful report if they are not.

    .. code-block:: c

        FCT_QTEST_BGN(chk_my_point) {
            point_t point1 = {1.f, 2.f, 3.f};
            point_t point2 = {1.f, 2.f, 3.f};
            point_t point3 = {10.f, 20.f, 30.f};
            point_chk_eq(point1, point2, DBL_EPSILON);
            point_chk_eq(point1, point3, DBL_EPSILON);
        }
        FCT_QTEST_END();
             
    in the above example, the second check should generate a test error.

.. cfunction:: fct_req(condition)

    *New in FCTX 1.1*. Evaluates the *condition*, and if it is false it will
    cause a test to fail.  This differs from :cfunc:`fct_chk` in so far as a
    false state causes the test block to abort.

