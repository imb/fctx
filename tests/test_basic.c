/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================
File: test_basic.c

Provides a dumping ground for basic tests of fct.
*/

#include "fct.h"

FCT_BGN()
{
   /* A very simple test suite, it doesn't have any data to 
   setup/teardown. */
   FCT_SUITE_BGN(simple)
   {
      /* A test, simply check that 1 is still 1. */
      FCT_TEST_BGN(simple__one_is_one)
      {
         fct_chk(1);
      }
      FCT_TEST_END();
   }
   FCT_SUITE_END();

      /* Test running with a fixture, where we need to setup and 
   teardown data. */
   FCT_FIXTURE_SUITE_BGN(fixture)
   {
      int a =0;
      int b =0; 
      int c =0;

      FCT_SETUP_BGN()
      {
         a =1;
         b =2;
         c =3;
      }
      FCT_SETUP_END();
   
      FCT_TEARDOWN_BGN()
      {
         a=0;
         b=0;
         c=0;
      }
      FCT_TEARDOWN_END();
       
      FCT_TEST_BGN(fixture__smoke_test)
      {
         // THE TEST CASE ...
         char const *test_str  = "test_str";
         fct_chk( strcmp(test_str, "test") != 0);
         fct_chk( strcmp(test_str, "test_str") == 0);
      }
      FCT_TEST_END();
      
      FCT_TEST_BGN(fixture__smoke_test_again)
      {
         fct_chk(1);
      }
      FCT_TEST_END();

  }
  FCT_FIXTURE_SUITE_END()

  /* A blank suite shouldn't cause a crash. */
  FCT_SUITE_BGN(blank)
  {
  }
  FCT_SUITE_END();

  /* Test the 'filtering' API */
  FCT_SUITE_BGN(filtering)
  {
     FCT_TEST_BGN(filtering__smoke_test)
     {
        int ok;

        ok = fct_filter_pass("filter", "filter__smoke_test");
        fct_chk( ok );

        /* This is an automatic pass. */
        ok = fct_filter_pass("filter", "filter");
        fct_chk( ok );

        /* This should fail, since the filter is LONGER than the test
        string.  */
        ok = fct_filter_pass("filter", "fil");
        fct_chk( !ok );

        ok = fct_filter_pass("filter", "green_eggs_and_ham");
        fct_chk( !ok );

        ok = fct_filter_pass("filter", "");
        fct_chk( !ok );
     }
     FCT_TEST_END();

     FCT_TEST_BGN(filtering__blank_or_null_filter_always_passes)
     {
        int ok;
      
        ok = fct_filter_pass("", "green_eggs_and_ham");
        fct_chk( ok );
        ok = fct_filter_pass(NULL, "green_eggs_and_ham");
        fct_chk( ok );

     }
     FCT_TEST_END();

  }
  FCT_SUITE_END();



}
FCT_END();


