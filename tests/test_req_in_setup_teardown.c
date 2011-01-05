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
    int ran_test =0; /* This should never be set to 1. */

    FCT_FIXTURE_SUITE_BGN(check_in_setup) {
        FCT_SETUP_BGN() {
            fct_req(0 && "cause a failure during setup");
        } FCT_SETUP_END();

        FCT_TEARDOWN_BGN() {
        } FCT_TEARDOWN_END();

        FCT_TEST_BGN(setup_test1) {
            fct_ts_t *ts_curr = fctkern_ptr__->ns.ts_curr;
            ts_curr =fctkern_ptr__->ns.ts_curr;

            /* We should never set this to 1. */
            ran_test =1;
            /* Need to statisfy a warning. */
            if ( ran_test ) {
               printf("ran test");
            }
        } FCT_TEST_END();
    } FCT_FIXTURE_SUITE_END();

    FCT_QTEST_BGN(verify_we_aborted) {
        fct_chk(ran_test == 0);
    } FCT_QTEST_END();

    printf("\n***TESTS ARE SUPPOSED TO REPORT FAILURES***\n");
    FCT_EXPECTED_FAILURES(1);
} FCT_END();

