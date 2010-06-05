/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================

File: custom_logger_fct.h

Extends the fct logger. 
*/

#include "fct.h"

/* Define our custom logger object. */
struct _fct_custom_logger_t {
    _fct_logger_head;   
};

static void
fct_custom_logger__on_chk(fct_logger_i *l, fct_logger_evt_t const *e) {
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
