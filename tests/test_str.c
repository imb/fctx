/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================
File: test_basic.c

Test the Check Routines, make sure they are doing what they are supposed to do.
*/

#include "fct.h"

FCT_BGN()
{
    FCT_QTEST_BGN(fctstr_envrepl__no_vars)
    {
        char *repl = fctstr_envrepl("boo");
        fct_req( repl != NULL );
        fct_chk_eq_str( repl, "boo");
        free(repl);
    }
    FCT_QTEST_END();

    FCT_QTEST_BGN(fctstr_envrepl__emptystr)
    {
        char *repl = fctstr_envrepl("");
        fct_req( repl != NULL );
        fct_chk_eq_str( repl, "");
        free(repl);
    }
    FCT_QTEST_END();
}
FCT_END();
