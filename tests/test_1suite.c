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

#include "fft.h"

FFT_BEGIN() 
{
   FFT_FIXTURE_SUITE_BEGIN("1Suite") 
   {
         FFT_SETUP_BEGIN() 
         {
         }
         FFT_SETUP_END();
      
         FFT_TEARDOWN_BEGIN()
         {
         }
         FFT_TEARDOWN_END();

         FFT_TEST_BEGIN("1Test")
         {
            fft_chk( strcmp("a", "b") != 0 );
         }
         FFT_TEST_END();

   } 
   FFT_FIXTURE_SUITE_END();

} 
FFT_END();