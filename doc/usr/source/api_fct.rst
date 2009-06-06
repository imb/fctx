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
