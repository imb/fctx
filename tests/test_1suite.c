/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================

File: test_1suite.c

Runs through 1 test suite. A very simple project for testing the layout 
and execution of a test suite.

*/

#include "fct.h"

FCT_BEGIN() 
{
   FCT_FIXTURE_SUITE_BEGIN("1Suite") 
   {
         FCT_SETUP_BEGIN() 
         {
         }
         FCT_SETUP_END();
      
         FCT_TEARDOWN_BEGIN()
         {
         }
         FCT_TEARDOWN_END();

         FCT_TEST_BEGIN("1Test")
         {
            fct_chk( strcmp("a", "b") != 0 );
         }
         FCT_TEST_END();

   } 
   FCT_FIXTURE_SUITE_END();

} 
FCT_END();
