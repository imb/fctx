=================
Customized Logger
=================

.. module:: custom logger
   :platform: Unix, Windows
   :synopsis: Provides ability to add your own customized logger.

.. versionadded:: 1.4

Introduction
------------

xxx

Building a Logger
-----------------

The following section will walk through the code shown in the source
tarball under :file:`/examples/custom_logger/custom_logger_fct.h`.

First, create a file that you will call as your header file, in this
file you will override certain behaviour found in the original
:file:`fct.h` file.

Next we will create our custom logger "object",

.. code-block:: c

	/* Define our custom logger object. */
	struct _custlog_t
	{
	    /* Define the common logger header. */
	    _fct_logger_head;
	    /* Add any data members you want to maintain here. Perhaps
	    you want to track something from event to event? */
	};

   #include "fct.h"

.. /*  fix vi styling.

This creates the object and ensures that the default definitions are
present at the start of the structure. These default definitions
define our "logger interface". The remaining data can be anything you
like to add for managing your logger information.

Now we will go through the process of adding an event handler for our
custom logger. The example in the source code will go over each
available event, but for our document we will discuss the event that
is executed when an fct_chk call is made. 

.. code-block:: c

   static void
   custlog__on_chk(fct_logger_i *l, fct_logger_evt_t const *e) {
   }

.. /* fix vi styling

At this point the *l* argument will point to your custom logger
defined above (i.e. struct _custlog_t), and the *e* argument will
provide you with details specific to this event. You may take your
logger, *i*, cast it to your logger type and add information, or you
may do something as simple as output a some informationa about the
check.

The next step is to define a creation method for your logger. This
creates up a new custom logger and returns a generic logger type
pointer. The following shows how to create your logger type, and set
the new `custlog__on_chk` function.

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

Finally, lets register our logger with FCTX, so the user can select it
and use it themselves,

.. code-block:: c

    struct fct_logger_types_t custlogs[] = {
	   {"custlog", (fct_logger_new_fn)custlog_new, 
	      "custom_logger_example!"},
	   {NULL, (fct_logger_new_fn)NULL, NULL} /* Sentinel */
    };

.. /* fix vi styling

will define a list of custom loggers to install. You can override the
standard logger here by defining a "standard" field. The last step is
to install our definition with FCTX via the :cfunc:`fctlog_install`
call. In our example, we will override the :cfunc:`FCT_BGN` and
:cfunc:`FCT_END` macros with our own custom macro, as in,

.. code-block:: c

   #define CL_FCT_BGN() \
       FCT_BGN() {      \
           fctlog_install(custlogs);
       
   /* For symmetry only. */
   #define CL_FT_END() } FCT_END()

.. /* fix vi styling

Now your code base can use the :cmacro:`CL_FCT_BGN` and
:cmacro:`CL_FCT_END` macros as well as your custom header to write
unit tests that follow and use your project's standard logging
methods.

Install Functions

.. cfunc:: fct_install(custlog)

   Installs the :ctype:`fct_logger_types_t` structure that defines the
   correct function to invoked based on a user selected option.  Fields
   in the *custlog* will override the default standards.

Useful Logger Types 
-------------------

fct_logger_i
fct_logger_evt_t
fct_logger_types_t

