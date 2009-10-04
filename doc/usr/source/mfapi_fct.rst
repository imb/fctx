===================
Multi-File FCTX API
===================

.. module:: FCTMF
   :platform: Unix, Windows
   :synopsis: FCTX across multiple files.

.. versionadded:: 1.1
   The FCTX Multi-File (FCTMF) supersedes the older "include method"
   described in version 1.0.

Introduction
------------

When you start unit testing with FCTX you will find that at some point
holding all your tests in one file can become unwieldy. The Multi-File api
(FCTMF) attempts to provide a minimal barrier to writing unit tests that span
multiple files.

The idea is to have one file that starts up tests defined in each of the other
files. The process of registration is a one step "call" into the other files.

Multi-File Setup
----------------

Lets pretend we have two files: :file:`test_main.c` and :file:`test_a.c`. In
:file:`test_main.c` we will setup and register our test that is defined in
:file:`test_a.c`.

Lets look at :file:`test_main.c`,

.. code-block:: c

   #include "fct.h"
   
   FCT_BGN() {
       FCTMF_SUITE_CALL(test_a_feature);
   } FCT_END();

there now we have set it up to call into the test suite called "test_a_feature"
defined in :file:`test_a.c`.  Lets look at the contents of :file:`test_a.c`.

.. code-block:: c

   #include "fct.h"

   FCTMF_SUITE_BGN(test_a_feature) {

       FCT_TEST_BGN(sanity_check) {
           fct_chk( a_feature__sanity_check() );
       } FCT_TEST_END();

   } FCTMF_SUITE_END();

this will register a test suite called "test_a_feature" and execute a test
called "sanity_check". 

If you wanted to use a test suite with fixtures (setup/teardown), you would do
the following,

.. code-block:: c
 
   #include "fct.h"

   static a_object_t *obj; 

   FCTMF_FIXTURE_SUITE_BGN(test_a_feature) {

       FCT_SETUP_BGN() {
           obj = a_object_new();
       } FCT_SETUP_END();

       FCT_TEARDOWN_BGN() {
           a_object__del(obj);
           obj =NULL;
       } FCT_TEARDOWN_END();

       FCT_TEST_BGN(sanity_check) {
           fct_chk( a_object__sanity_check(obj) );
       } FCT_TEST_END()

   } FCTMF_FIXTURE_SUITE_END();

.. /* (Just fixes VIM highligher)

the only difference here being the introduction of "FIXTURE" into scope
statements as well as the SETUP and TEARDOWN fixtures themselves.

The key thing to also notice is that all the testing, checking, setup and
teardown macros follow the existing :mod:`FCT` module. 
   
Multi-File Test Suites
----------------------

.. cfunction:: FCTMF_SUITE_CALL(name)

        This launches the test suite defined by *name*. You would place this
        call between the :cfunc:`FCT_BGN()` and :cfunc:`FCT_END()` scope. This
        simply calls off to another file, and it does not prevent you from
        having other tests within the :cfunc:`FCT_BGN()` and :cfunc:`FCT_END()`
        scope.

.. cfunction:: FCTMF_FIXTURE_SUITE_BGN(name)
	
	Following the xtest convention, every test suite needs to start with a 
	SUITE_BGN function. In by using the FIXTURE variants you are indicating
	that you wish to install a SETUP and TEARDOWN fixture via the
	:cfunc:`FCT_SETUP_BGN` and :cfunc:`FCT_SETUP_END` and
	:cfunc:`FCT_TEARDOWN_BGN` and :cfunc:`FCT_TEARDOWN_END` functions.

	See also :cfunc:`FCTMF_SUITE_BGN`.

.. /*  (Just fixes VIM highlighter)

.. cfunction:: FCTMF_FIXTURE_SUITE_END(name)

	This closes a test suite that contains fixtures. If you do not wish to
	specify a setup/teardown you would use the :cfunc:`FCT_SUITE_END` 
	function instead.

.. cfunction:: FCTMF_SUITE_BGN(name)

        Use this FCTMF_SUITE variant if you do not want to bother specifying a
        SETUP and TEARDOWN blocks.

        See also :cfunc:`FCTMF_FIXTURE_SUITE_BGN`.

.. cfunction:: FCTMF_SUITE_END()

        Closes the :cfunc:`FCTMF_SUITE_BGN` function.

