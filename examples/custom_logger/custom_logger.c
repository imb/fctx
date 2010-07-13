/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================

File: custom_logger.c
*/

/* Rather than include fct, we will include our 'custom_logger_fct.h'
header. This header will be responsible for exentending the logger.  */
#include "custom_logger_fct.h"

CL_FCT_BGN() {
   FCT_QTEST_BGN(custom_logger_test1) {
      fct_chk("pass");
   } FCT_QTEST_END();
} CL_FCT_END();
