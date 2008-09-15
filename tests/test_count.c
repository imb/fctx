/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================

Tests "counting" of various elements of a unit test framework. For
example the number of tests, the number of checks, &etc.

TODO - Run this in verbose mode.
*/

#include "fft.h"

FFT_BEGIN()
{
   /* An empty test suite that doesn't have any tests within
   it, then confirm that at our count is still zero. */
   FFT_SUITE_BEGIN(empty)
   {
   }
   FFT_SUITE_END();
   _FFT_GUTCHK(fftkern__tst_cnt(&fftkern__) == 0);

   /* Now run a suite again, but place one test in it. Then confirm with
   our gut check. */
   FFT_SUITE_BEGIN(one_test)
   {
      FFT_TEST_BEGIN(check_one_test)
      {
      }
      FFT_TEST_END();
   }
   FFT_SUITE_END();
   _FFT_GUTCHK(fftkern__tst_cnt(&fftkern__) == 1);
   _FFT_GUTCHK(fftkern__chk_cnt(&fftkern__) == 0);

   /* Now again, but with two checks. The gut check should return 3 for the
   number of tests. */
   FFT_SUITE_BEGIN(one_test_again)
   {
      FFT_TEST_BEGIN(check_one_test_again)
      {
         fft_chk(1);
         fft_chk(1);
      }
      FFT_TEST_END();
   }
   FFT_SUITE_END();
   _FFT_GUTCHK(fftkern__tst_cnt(&fftkern__) == 2);
   _FFT_GUTCHK(fftkern__chk_cnt(&fftkern__) == 2);

   
}
FFT_END();


