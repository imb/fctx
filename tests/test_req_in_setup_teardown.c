/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================
File: test_req_in_setup_teardown.c

Tests running fct_req within a setup and teardown.
*/

#include "fct.h"

FCT_BGN() {

    FCT_FIXTURE_SUITE_BGN(check_in_setup) {
        FCT_SETUP_BGN() {
            fct_req(0);
        } FCT_SETUP_END();

        FCT_TEARDOWN_BGN() {
        } FCT_TEARDOWN_END();

        FCT_TEST_BGN(setup_test1) {
            /* We should never set this to 1. */
            int ran_test =1;
            /* Need to statisfy a warning. */
            if ( ran_test ) {
                printf("ran test");
            }
        } FCT_TEST_END();
    } FCT_FIXTURE_SUITE_END();


} FCT_END();

