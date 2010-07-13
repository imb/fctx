/* Extends the fct logger.

====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================

File: custom_logger_fct.h
*/

#include "fct.h"

/* Define our custom logger object. */
struct _cust_logger_t {
     /* Define the common logger header. */
     _fct_logger_head;
     /* Add any data members you want to maintain here. Perhaps
     you want to track something from event to event? */
};


/* Handles what to do when a fct_chk is made. */
static void
cust_logger__on_chk(fct_logger_i *l, fct_logger_evt_t const *e) {
    fct_unused(l);
    fctchk_t const *chk = e->chk;
    printf("on_chk: %s (%s)\n"
           "    -  location: %s(%d)\n"
           "    -   message: %s\n",
           fctchk__cndtn(chk),
           (fctchk__is_pass(chk)) ? "PASS" : "FAIL",
           fctchk__file(chk),
           fctchk__lineno(chk),
           fctchk__msg(chk)
   );
}


static fct_logger_i*
cust_logger_new(void) {
   struct _cust_logger_t *logger = (struct _cust_logger_t*)malloc(
					 sizeof(struct _cust_logger_t)
                                 );
  if ( logger == NULL ) {
     return NULL;
  }
  fct_logger__init((fct_logger_i*)logger);
  logger->vtable.on_chk = cust_logger__on_chk;
  return (fct_logger_i*)logger;
}


/* Define our custom logger structure. */


/* Define how to install the custom logger. To override the built in
ones use the same name (i.e. "standard" to override the default logger). */
static fct_logger_types_t cust_loggers[] = {
   {"standard", (fct_logger_new_fn)cust_logger_new},
   {NULL, (fct_logger_new_fn)NULL} /* Sentinel */
};


/* Redefine how to initialize FCT to automatically initialize our custom
logger. Define the _END macro for symmetry. */
#define CL_FCT_BGN()                 \
   FCT_BGN() {                       \
      fctlog_install(cust_loggers);

#define CL_FCT_END() } FCT_END()
