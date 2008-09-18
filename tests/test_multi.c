/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================
File: test_multi.c

This file will reference two other files to get the test suites.
*/

#include "fct.h"

FCT_BGN()
{
#include "test_multi_suite_a.h"
#include "test_multi_suite_b.h"
}
FCT_END();