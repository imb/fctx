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
struct _custlog_t {
     /* Define the common logger header. */
     _fct_logger_head;
     /* Add any data members you want to maintain here. Perhaps
     you want to track something from event to event? */
};


/* Handles what to do when a fct_chk is made. */
static void
custlog__on_chk(fct_logger_i *l, fct_logger_evt_t const *e) {
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

static void
custlog__on_test_start(fct_logger_i *, fct_logger_evt_t const *e) {
}


static void
custlog__on_test_end(fct_logger_i *, fct_logger_evt_t const *e) {
}

static void
custlog__on_test_start(fct_logger_i *, fct_logger_evt_t const *e) {
}

static void
custlog__on_test_suite_start(fct_logger_i *, fct_logger_evt_t const *e) {
}

static void
custlog__on_test_suite_end(fct_logger_i *, fct_logger_evt_t const *e) {
}

static void
custlog__on_fctx_start(fct_logger_i *, fct_logger_evt_t const *e) {
}

static void
custlog__on_fctx_end(fct_logger_i *, fct_logger_evt_t const *e) {
}

static void
custlog__on_warn(fct_logger_i *, fct_logger_evt_t const *e) {
}

static void
custlog__on_test_suite_skip(fct_logger_i *, fct_logger_evt_t const *e) {
}

static void
custlog__on_test_skip(fct_logger_i *, fct_logger_evt_t const *e) {
}

static void
custlog__on_delete(fct_logger_i *, fct_logger_evt_t const *e) {
}


static fct_logger_i*
custlog_new(void) {
   struct _custlog_t *logger = (struct _custlog_t*)malloc(
					 sizeof(struct _custlog_t)
                                 );
  if ( logger == NULL ) {
     return NULL;
  }
  fct_logger__init((fct_logger_i*)logger);
  /* The destructor. */
  logger->vtable.on_delete = custlog__on_delete;
  /* The event handlers. */
  logger->vtable.on_chk = custlog__on_chk;
  logger->vtable.on_test_start = custlog__on_test_start;
  logger->vtable.on_test_end = custlog__on_test_end;
  logger->vtable.on_test_suite_start = custlog__on_test_suite_start;
  logger->vtable.on_test_suite_end = custlog__on_test_suite_end;
  logger->vtable.on_fctx_start = custlog__on_fctx_start;
  logger->vtable.on_fctx_end = custlog__on_fctx_end;
  logger->vtable.on_warn = custlog_on_warn;
  logger->vtable.on_test_suite_skip =  custlog__on_test_suite_skip;
  logger->vtable.on_test_skip = custlog__on_test_skip;
  return (fct_logger_i*)logger;
}


/* Define our custom logger structure. */


/* Define how to install the custom logger. To override the built in
ones use the same name (i.e. "standard" to override the default logger). */
static fct_logger_types_t custlogs[] = {
   {"custlog", (fct_logger_new_fn)custlog_new},
   {NULL, (fct_logger_new_fn)NULL} /* Sentinel */
};


/* Redefine how to initialize FCT to automatically initialize our custom
logger. Define the _END macro for symmetry. */
#define CL_FCT_BGN()                 \
   FCT_BGN() {                       \
      fctlog_install(custlogs);

#define CL_FCT_END() } FCT_END()
