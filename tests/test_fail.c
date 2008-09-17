/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================
File: test_fail.c

This code is designed to fail. It runs tests to confirm that failure conditions are failing properly.
*/

#include "fft.h"

FFT_BEGIN()
{
   /* A very simple test suite, it doesn't have any data to 
   setup/teardown. */
   FFT_SUITE_BEGIN(should_fail)
   {
      /* A test, simply check that 1 is still 1. */
      FFT_TEST_BEGIN(false is fail)
      {
         fft_chk(0);
      }
      FFT_TEST_END();
   }
   FFT_SUITE_END();

}
FFT_END();


