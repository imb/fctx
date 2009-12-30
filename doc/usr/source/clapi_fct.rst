========================
FCT_CL: Command Line API
========================

.. module:: FCT_CL 
   :platform: Unix, Windows
   :synopsis: FCTX command line interface.

.. versionadded:: 1.2

Introduction
------------

To help control unit tests at runtime you may want to use command line
arguments. This modules provides access to a simple command line parser that
builds into each version FCTX unit testing application.

Built-in Options
----------------

When you build a program with FCTX, you will get a set of pre-built command
line options. The options are as follows,

.. program:: fctx_program.exe

.. cmdoption:: -v, --version

 Reports the version of FCTX used to build ``your_test_program.exe``.

.. cmdoption:: -h, --help

 Shows the usage for all command line options defined for
 ``your_test_program.exe``.

The following options are reserved, and should not be used by your custom
command line options.

.. program:: fctx_program.exe

.. cmdoption:: -l, --logger

 Defines a logger. Currently not defined, but in the future we would like
 to be able to define the type of logger used.

All all future pre-built command line options in FCTX will all be prefixed with
a "f", as in ``--foption``.

Customizing the Command Line
----------------------------

The following steps go over how to set up your own custom command line parser
and check the results.

In our example we will test for a "flag" option called ``--use-slow``, which
when present will signal that we can execute the long running unit tests.  You
could envisage using this option for a nightly run only, while day-to-day work
would avoid the long running tests.

First, lets take a look at what we have before we customize the command line
parser.

.. code-block:: c

   #include "fct.h"
   FCT_BGN() {
       int use_slow =0; /* Toggle This Value */
       FCT_QTEST_BGN(slow_test) {
           if ( use_slow ) {
               fct_chk( run_slow_running_process() );
           } 
       } FCT_QTEST_END();
   } FCT_END();

.. /* (Fixes VIM highlighter)

now in order to determine if you want to run the slow tests you need to toggle
the *use_slow* variable to true and re-compile. Clearly this is not a desirable
way to control the execution.

What follows is how to go about setting up a custom command line option so we
can check if the *use_slow* option should be set to true at run-time.

The first thing we will do is install our command line options. This is a NULL
terminated list of :ctype:`fct_clo_init_t` entries. 

.. code-block:: c

   #include "fct.h"

   /* Add our command line options. */
   static fct_clo_init_t my_cl_options[] = {
       {"--use-slow",                   /* long_opt */
        NULL,                           /* short_opt (optional) */
        FCT_CLO_STORE_TRUE,             /* action */
        "Runs slow running unit tests"  /* help */
        },
       FCT_CLO_INIT_NULL /* Sentinel */
   };

   FCT_BGN() {
       int use_slow =0; /* Toggle This Value */
       FCT_QTEST_BGN(slow_test) {
           if ( use_slow ) {
               fct_chk( run_slow_running_process() );
           } 
       } FCT_QTEST_END();
   } FCT_END();

.. /* (Fixes VIM highlighter)

The entry we added says: "if you encounter the long ``--use-slow`` option, then
set a true flag that we can read later."

Next we install the options with the :cfunc:`FCT_CL_INSTALL`.

.. code-block:: c

   #include "fct.h"

   /* Add our command line options. */
   static fct_clo_init_t my_cl_options[] = {
       {"--use-slow", 
        NULL, 
        FCT_CLO_STORE_TRUE, 
        "Runs slow running unit tests"},
       FCT_CLO_INIT_NULL /* Sentinel */
   };

   FCT_BGN() {
       int use_slow =0; 
        
       /* Install the command line options defined above. */
       FCT_CL_INSTALL(my_cl_options);

       /* Check if --use-slow was on the command line. */
       use_slow = FCT_CL_IS("--use-slow");

       FCT_QTEST_BGN(slow_test) {
           if ( use_slow ) {
               fct_chk( run_slow_running_process() );
           } 
       } FCT_QTEST_END();
   } FCT_END();

.. /* (Fixes VIM highlighter)

After you have installed the options you can now check if a flag is set using
the :cfunc:`FCT_CL_IS` macro. If the user had entered ``--use-slow`` at the
command prompt, then the value of :cfunc:`FCT_CL_IS` would return TRUE (1).

Types
-----

.. ctype:: fct_clo_init_t

   Use this structure to initialize your options. The structure is usually
   initialized as part of a listing of command line options. Each filed is
   described below.

   .. cmember:: char const * long_opt

      Long option on the command line.

   .. cmember:: char const * short_opt

      Short option on the command line. This can be set to NULL if you do not
      wish to have a short option available.

   .. cmember:: fct_clo_store_t action

      When a command line option is encountered by the parser this describes
      what the parser should do. If, for example, :cmacro:`FCT_CLO_STORE_TRUE`
      is used, then a true boolean value (1) is stored. If
      :cmacro:`FCT_CLO_STORE_VALUE` is used, then a string is stored and can be
      later retrieved.

   .. cmember:: char const * help

      This is the help string that is displayed if the command line parser
      encounters a ``-h`` or ``--help``.

.. ctype:: fct_clo_store_t

     Describes the action to take if a command line option is recognized by the
     parser. Valid options currently are,

     .. cmacro:: FCT_CLO_STORE_UNDEFINED
         
        Do not use. This is the default value when we don't have an available
        option.

     .. cmacro:: FCT_CLO_STORE_TRUE

        When present it signals to the command line parser that we store a true
        (1) flag.

     .. cmacro:: FCT_CLO_STORE_VALUE

        When present it signals to the command line parser that we store a
        string value corresponding to the next argument in the parser. For
        instance,

           ===============  ===============
           Command Line     Resulting Value
           ===============  ===============
           --use-value=xxx  xxx
           --use-value xxx  xxx
           ===============  ===============
          
        use this if you want to retrieve a value from the command line.

Functions
---------

.. cfunction:: int FCT_CL_IS(flag)

   Returns true if the *flag* has been used. The *flag* is the either the long
   or short option used during the configuration stage. Use this macro to
   retrieve :cmacro:`FCT_CLO_STORE_TRUE` command line options.

.. cfunction:: const char* FCT_CL_VAL(flag)

   Returns a character buffer defined by the *flag*. It will return NULL if
   *flag* was not defined at the command line. Use this macro to retrieve
   :cmacro:`FCT_CLO_STORE_VALUE` command line options. 

.. cfunction:: const char * FCT_CL_VAL2(flag, defval)

   Returns a character buffer defiend by the *flag* or the pointer to *defval*
   if the *flag* was not defined on the command line. Use this macro to
   retrieve :cmacro:`FCT_CLO_STORE_VALUE` command line options.
