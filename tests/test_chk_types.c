/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================
File: test_chk_types.c

*/

#include <float.h>
#include "fct.h"

FCT_BGN()
{
    FCT_QTEST_BGN(chk_dbl_eq)
    {
        fct_chk_eq_dbl(6123.2313,6123.2313);
    }
    FCT_QTEST_END();

    FCT_QTEST_BGN(chk_dbl_neq)
    {
        fct_chk_neq_dbl(1.11111, 1.1);
    }
    FCT_QTEST_END();
}
FCT_END();
