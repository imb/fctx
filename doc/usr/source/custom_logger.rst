=============================
fct_logger: Customized Logger
=============================

.. module:: fct_logger
   :platform: Unix, Windows
   :synopsis: Provides ability to add your own customized logger.

.. versionadded:: 1.4

Introduction
------------

FCTX is built with default loggers, but these loggers may not be
suitable for your project or organization. The FCTX API provides a
method for you to customize your own logger by defining and installing
logger type that can handle events that occur during unit testing.

Your organization or project can then be directed to use this custom
logger as the standard method for logging when writing unit tests
using FCTX.

Building a Logger
-----------------

The following section will walk through the code shown in the source
tarball under :file:`/examples/custom_logger/custom_logger_fct.h`.

First, create a file that you will use as your project standard header
file, in this file you will override certain behaviour found in the
original :file:`fct.h` file. For logging we we will start with our
custom logger type,

.. code-block:: c

        /* Load the FCTX API */
        #include "fct.h"

	/* Define our custom logger object. */
	struct _custlog_t
	{
	    /* Define the common logger header. */
	    _fct_logger_head;
	    /* Add any data members you want to maintain here. Perhaps
	    you want to track something from event to event? Lets
            count the number of checks. */
            size_t num_chks;
	};


.. /*  fix vi styling.

This creates the object and ensures that the default definitions are
present at the start of the structure. These default definitions
define our "logger interface". The remaining data can be anything you
like to add for managing your logger information.

Now we will go through the process of adding an event handler for our
custom logger. The example in the source code will go over each
available event, but for our document we will discuss the event that
is executed when an :c:func:`fct_chk` call is made. 

.. code-block:: c

   static void
   custlog__on_chk(fct_logger_i *l, fct_logger_evt_t const *e) {
      struct *_custlog_t = (struct _custlog_t*)l;
      fct_unused(e); /* In this example, we will ignore it. */
      ++(l->num_chks);
   }

.. /* fix vi styling

At this point the *l* argument will point to your custom logger
defined above (i.e. struct _custlog_t), and the *e* argument will
provide you with details specific to this event (see
:ref:`fct_logger_events`). You may take your logger, *i*, cast it to
your logger type and add information, or you may do something as
simple as output a some information about the check.

The next step is to define a creation method for your logger. This
should create new custom logger and returns a generic logger type
pointer. The following shows how to create your logger type, and set
the new :c:func:`custlog__on_chk` function.

.. code-block:: c

   static fct_logger_i *
   custlog_new(void) {
      struct _custlog_t *logger = (struct _custlog_t*)malloc(
                                       sizeof(struct _custlog_t)
                                  );
       if ( logger == NULL ) {
           return NULL;	/* Out of memory, not likely. */
       }
       /* Initialize the common logger interface. */
       fct_logger__init((fct_logger_i*)logger);
       /* Define our destructor, assume you have written something
       that cleans up after yourself. */
       logger->vtable.on_delete = custlog__on_delete;
       logger->vtable.on_chk = custlog__on_chk;
       return (fct_logger_i*)logger;
   }
       
This will create, install and return your custom logger, but we still
need to write our delete function, 

.. code-block:: c

   static void
   custlog__on_delete(fct_logger_i *l, fct_logger_evt_t const *e) {   
      fct_unused(e);
      free((struct _custlog_t*)l);
   }

in our demo we don't have much to clean up other than the object we
allocated.

Once we have defined our custom logger, we need to associate it with a
command so the user can select it from the command prompt. We do it
via the :c:type:`fct_logger_types_t` as shown below,

.. code-block:: c

    struct fct_logger_types_t custlogs[] = {
	   {"custlog", (fct_logger_new_fn)custlog_new, 
	      "custom_logger_example!"},
	   {NULL, (fct_logger_new_fn)NULL, NULL} /* Sentinel */
    };

.. /* fix vi styling

will define a list of custom loggers to install. You can override the
standard logger here by defining a "standard" field. The last step is
to install our definition with FCTX via the :c:func:`fctlog_install`
call. In our example, we will override the :c:func:`FCT_BGN` and
:c:func:`FCT_END` macros with our own custom macro, as in,

.. code-block:: c

   #define CL_FCT_BGN() \
       FCT_BGN() {      \
           fctlog_install(custlogs);
       
   /* For symmetry only. */
   #define CL_FT_END() } FCT_END()

.. /* fix vi styling

Now your code base can use the :c:macro:`CL_FCT_BGN` and
:c:macro:`CL_FCT_END` macros as well as your custom header to write
unit tests that follow and use your project's standard logging
methods.

Assuming the program generated was called :file:`test.exe`, the
custom logger would be invoked with::

  test.exe --logger=custlog

If you use the ``--help`` option you get a list of available loggers
that will include your custom logger.

Install Functions
-----------------

.. c:function:: fct_install(custlog)

   Installs the :ctype:`fct_logger_types_t` structure that defines the
   correct function to invoked based on a user selected option.  Fields
   in the *custlog* will override the default standards.

.. _fct_logger_events:

Events
------

The sample code found in the source tree under
:file:`/examples/custom_logger` directory illustrates in code, what
you can extract from a particular logging event.

.. _fct_logger_on_chk:

On fct_chk
..........

:c:member:`vtable.on_chk`.

xxx

On FCT_TEST_BGN
...............

:c:member:`vtable.on_test_start`

xxx

On FCT_TEST_END
...............

:c:member:`vtable.on_test_end`

xxx

On FCT_TEST_SUITE_BGN
......................

:c:member:`vtable.on_test_suite_start`

xxx

On FCT_TEST_SUITE_END
.....................

:c:member:`vtable.on_test_suite_end`

xxx

On FCTX Start
.............

:c:member:`vtable.on_fctx_start`

xxx

On FCTX End
...........

:c:member:`vtable.on_fctx_end`

xxx

On Warn
.......

:c:member:`vtable.on_warn`

xxx

On Test Suite Skip
..................

:c:member:`vtable.on_test_suite_skip`

xxx

On Test Skip
............

:c:member:`vtable.on_test_skip`

xxx


Useful Logger Types 
-------------------

fct_logger_i
fct_logger_evt_t
fct_logger_types_t

