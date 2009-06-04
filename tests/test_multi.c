/*
====================================================================
Copyright (c) 2009 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================
File: test_multi.c

This code is designed to experiment with the "multi-file" support 
for the FCT.

This method superscedes the test_mutli_old_style method shown in the other
test example. As it doesn't suffer from some of the foibles in that
method.
*/

#include "fct.h"

/* You can get away without defining this if you don't mind a warning
about a function not being defined. The linker will make it all work
in the end. However, if you like to be formal, you need to specify this
line. */
FCTMF_SUITE_DEF(test_suite1);
FCTMF_SUITE_DEF(test_fixture_suite2);

FCT_BGN() { 
    /* This suite is called *OUTSIDE* of this compilation unit. */
    FCTMF_SUITE_CALL(test_suite1);
	FCTMF_SUITE_CALL(test_fixture_suite2);
    
    /* Provide a co-existing "embedded" version for completness. */
    FCT_SUITE_BGN(test_embedded) {
        FCT_TEST_BGN(test_embedded.zero_is_zero) {
            fct_chk( 0 == 0 );
        } FCT_TEST_END();
    } FCT_SUITE_END();
} FCT_END();
