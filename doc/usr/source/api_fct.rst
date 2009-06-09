================
FCT Initializers
================

.. module:: FCT
   :platform: Unix, Windows
   :synopsis: Begin and End your test framework.


Initialize/Finalize
-------------------

.. cfunction:: FCT_BGN()

	Initializes your test framework. Every test program needs to begin with
	this declaration.

.. cfunction:: FCT_END()

	Finalizes your test framwork. Every test program neesd to end with this
	declaration.

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


.. cfunction:: FCT_FIXTURE_SUITE_END(name)

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

        Closes the FCT_SUITE_BGN function.

.. cfunction:: FCT_SETUP_BGN()

        Opens a SETUP block. This block is executed *before* every test.

.. cfunction:: FCT_SETUP_END()
   
        Closes the SETUP block.

.. cfunction:: FCT_TEARDOWN_BGN()

        Opens up a teardown block. This block is executed *after* every test.

.. cfunction:: FCT_TEARDOWN_END()

        Ends a teardown block. 


Quick Test
----------

*New in FCTest 1.1*. This allows you to write tests without any Test Suite
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

.. cfunction:: FCT_TEST_END()

   Ends the quick test block.


Tests
-----

These define a beginning and end of a test block. See also
:cfunc:`FCT_QTEST_BGN` and :cfunc:`FCT_QTEST_END`.

.. cfunction:: FCT_TEST_BGN(name)

   Opens a test block with the given *name*.

.. cfunction:: FCT_TEST_END()

   Closes a test block. 


Checks
------

These are used to verify that a condition is true. They are executed within
:cfunc:`FCT_TEST_BGN`/:cfunc:`FCT_TEST_END` blocks. 


.. cfunction:: fct_chk(condition)

    Evaluates the condition, and if it is false will cause the tests to fail.
    Further lines in the test block continue to execute. If you want a check to
    terminate testing, then use the :cfunc:`fct_req` function instead.

.. cfunction:: fct_req(condition)

    Evaluates the condition, and if it is false it will cause a test to fail.
    This differs from :cfunc:`fct_chk` in so far as a false state causes
    the test block to abort.
