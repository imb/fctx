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

This is build from the "JUnit Test Infected: Programmers Love Writing
Tests" paper found at the following URL, 
http://junit.sourceforge.net/doc/testinfected/testing.htm.
*/

/* Include the FCT Unit Test framework. */
#include "fct.h"

/* 
-----------------------------------------------------------------------
MONEY
-----------------------------------------------------------------------

Defines a "Simple" money object.
*/

/* Any currency "nickname" large than 16 must be a preversion of a
nickname. */
#define MONEY_MAX_CURR_LEN 16

typedef struct _money_t money_t;
struct _money_t 
{
   int amount;
   char currency[MONEY_MAX_CURR_LEN];
};

static void
money__del(money_t *money) 
{
   if ( money == NULL ) { return; }
   free(money);
}


static money_t *
money_new(int amount, char const *currency) 
{
   money_t *money =NULL;
   int curr_len =0;

   money = calloc(1, sizeof(money_t));
   if ( money == NULL )
   {
      return NULL;
   }
   
   strcpy(money->currency, currency);
   money->currency[MONEY_MAX_CURR_LEN-1] = '\0';

   money->amount = amount;

   return money;
}


static int
money__amount(money_t const *money)
{
   assert( money != NULL );
   return money->amount;
}

/* Returns a reference to the "currency string". Do NOT MODIFY! */
static char const *
money___currency(money_t const *money)
{
   assert( money != NULL );
   return money->currency;
}

static money_t*
money_add(money_t const *money1, money_t const *money2)
{
   money_t *new_amt =NULL;

   assert( money1 != NULL );
   assert( money2 != NULL );

   new_amt = money_new(
      money__amount(money1)+money__amount(money2),
      money___currency(money1)
      );
   return new_amt;
}

/* Returns 1 if money1 == money2 */
static int
money_eq(money_t const *money1, money_t const *money2)
{
   int is_same_curr =0;
   int is_same_amt =0;


   /* Are they pointing to the same memory, then they are the same object. 
   This also catches the case when they are both NULL. */
   if ( money1 == money2 ) 
   {
      return TRUE; 
   }

   /* If money1 XOR money2 are NULL, then we kick out. */
   if ( 
      (money1 == NULL && money2 != NULL) \
      || (money1 != NULL && money2 == NULL) 
      )
   {
      return FALSE;
   }

   /* At this point we shouldn't have any NULL money objects. */
   assert( money1 != NULL );
   assert( money2 != NULL );

   is_same_amt = money__amount(money1) == money__amount(money2);
   if ( !is_same_amt )
   {
      return FALSE;
   }

   is_same_curr = strcmp(money___currency(money1), money___currency(money2)) ==0;

   /* If they are the same currency, and the passed the eariler tests, then 
   they are the same object. */
   return is_same_curr;
}



/* 
-----------------------------------------------------------------------
UNIT TESTS
-----------------------------------------------------------------------
*/

FCT_BGN() 
{
   
   /* Illustrates a VERY SIMPLE unit test, without a fixture. */
   FCT_SUITE_BGN(money_simple)
   {
      FCT_TEST_BGN(money_new_del__basic)
      {
         money_t *m = money_new(10, "US");
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

   /* Creates a unit with a fixture, to help bootstrap common code between
   tests. */
   FCT_FIXTURE_SUITE_DECL()
   {
      /* These objects are common to each test. */
      money_t *m12CHF =NULL;
      money_t *m14CHF =NULL;

      FCT_FIXTURE_SUITE_BGN(money_fixture)
      {
         FCT_SETUP_BGN()
         {
            /* Our common setup procedure. */
            m12CHF = money_new(12, "CHF");
            m14CHF = money_new(14, "CHF");
         }
         FCT_SETUP_END();

         FCT_TEARDOWN_BGN()
         {
            /* Our common cleanup procedure. */
            money__del(m12CHF);
            m12CHF =NULL;
            money__del(m14CHF);
            m14CHF =NULL;
         }
         FCT_TEARDOWN_END();

         FCT_TEST_BGN(money_add__simple)
         {
            money_t *expected = money_new(26, "CHF");
            money_t *result = money_add(m12CHF, m14CHF);

            fct_chk( money_eq(result, expected) );
         }
         FCT_TEST_END();

         FCT_TEST_BGN(money_eq__simple)
         {
            money_t *m12CHF_prime = money_new(12, "CHF");

            fct_chk( !money_eq(m12CHF, NULL) );
            fct_chk(  money_eq(m12CHF, m12CHF) );
            fct_chk(  money_eq(m12CHF, m12CHF_prime) );
            fct_chk( !money_eq(m12CHF, m14CHF) );
         }
         FCT_TEST_END();

      }
      FCT_FIXTURE_SUITE_END();
   }





}
FCT_END();
