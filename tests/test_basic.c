/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================
File: test_basic.c

Provides a dumping ground for basic tests of fft.
*/

#include "fft.h"

FFT_BEGIN()
{
   /* A very simple test suite, it doesn't have any data to 
   setup/teardown. */
   FFT_SUITE_BEGIN(simple)
   {
      /* A test, simply check that 1 is still 1. */
      FFT_TEST_BEGIN(simple__one_is_one)
      {
         fft_chk(1);
      }
      FFT_TEST_END();
   }
   FFT_SUITE_END();

      /* Test running with a fixture, where we need to setup and 
   teardown data. */
   FFT_FIXTURE_SUITE_BEGIN(fixture)
   {
      int a =0;
      int b =0; 
      int c =0;

      FFT_SETUP_BEGIN()
      {
         a =1;
         b =2;
         c =3;
      }
      FFT_SETUP_END();
   
      FFT_TEARDOWN_BEGIN()
      {
         a=0;
         b=0;
         c=0;
      }
      FFT_TEARDOWN_END();
       
      FFT_TEST_BEGIN(fixture__smoke_test)
      {
         // THE TEST CASE ...
         char const *test_str  = "test_str";
         fft_chk( strcmp(test_str, "test") != 0);
         fft_chk( strcmp(test_str, "test_str") == 0);
      }
      FFT_TEST_END();
      
      FFT_TEST_BEGIN(fixture__smoke_test_again)
      {
         fft_chk(1);
      }
      FFT_TEST_END();

  }
  FFT_FIXTURE_SUITE_END()

  /* A blank suite shouldn't cause a crash. */
  FFT_SUITE_BEGIN(blank)
  {
  }
  FFT_SUITE_END();

  /* Test the 'filtering' API */
  FFT_SUITE_BEGIN(filtering)
  {
     FFT_TEST_BEGIN(filtering__smoke_test)
     {
        int ok;

        ok = fft_filter_pass("filter", "filter__smoke_test");
        fft_chk( ok );

        /* This is an automatic pass. */
        ok = fft_filter_pass("filter", "filter");
        fft_chk( ok );

        /* This should fail, since the filter is LONGER than the test
        string.  */
        ok = fft_filter_pass("filter", "fil");
        fft_chk( !ok );

        ok = fft_filter_pass("filter", "green_eggs_and_ham");
        fft_chk( !ok );

        ok = fft_filter_pass("filter", "");
        fft_chk( !ok );
     }
     FFT_TEST_END();

     FFT_TEST_BEGIN(filtering__blank_or_null_filter_always_passes)
     {
        int ok;
      
        ok = fft_filter_pass("", "green_eggs_and_ham");
        fft_chk( ok );
        ok = fft_filter_pass(NULL, "green_eggs_and_ham");
        fft_chk( ok );

     }
     FFT_TEST_END();

  }
  FFT_SUITE_END();



}
FFT_END();


