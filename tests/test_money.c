/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================
File: test_money.c

Emulates the testing a "Money" class. This is an example of testing
with something that is a little more "Real World". At least it 
corresponds to the oft written about class.
*/

/* Include the FCT Unit Test framework. */
#include "fct.h"

/* 
-----------------------------------------------------------------------
MONEY
-----------------------------------------------------------------------

Defines a "Simple" money object.
*/

typedef struct _Money_t Money_t;
struct _Money_t 
{
   void *dummy;
};

Money_t *
money_new(void) 
{
   return malloc(sizeof(Money_t));
}

void
money__del(Money_t *money) 
{
   if ( money == NULL ) { return; }
   free(money);
}

/* 
-----------------------------------------------------------------------
UNIT TESTS
-----------------------------------------------------------------------
*/

FCT_BGN() 
{
   
   FCT_SUITE_BGN(money_simple)
   {
      FCT_TEST_BGN(money_new_del__basic)
      {
         Money_t *m = money_new();
         fct_chk(m != NULL);
         money__del(m);
      }
      FCT_TEST_END();

      FCT_TEST_BGN(money_del__with_null)
      {
         /* Supply NULL to money_del, and make sure it does nothing. */
         money__del(NULL);
      }
      FCT_TEST_END();
   }
   FCT_SUITE_END();



}
FCT_END();
