/*
File: test_money.c

TODO: Copyright
TODO: Description ... emulates the testing a "Money" class. 
*/

/* Include the FFT Unit Test framework. */
#include "fft.h"

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

FFT_BEGIN() 
{
   
   FFT_SUITE_BEGIN(money_simple)
   {
      FFT_TEST_BEGIN(money_new_del__basic)
      {
         Money_t *m = money_new();
         fft_chk(m != NULL);
         money__del(m);
      }
      FFT_TEST_END();

      FFT_TEST_BEGIN(money_del__with_null)
      {
         /* Supply NULL to money_del, and make sure it does nothing. */
         money__del(NULL);
      }
      FFT_TEST_END();
   }
   FFT_SUITE_END();



}
FFT_END();
