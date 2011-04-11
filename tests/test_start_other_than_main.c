/*
====================================================================
Copyright (c) 2011 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================
File: test_start_other_than_main.c
*/

#include "fct.h"

int
_start_test(int argc, char *argv[]) {
    FCT_INIT(argc, argv);

    FCT_QTEST_BGN(test_with_my_own_func) {
        fct_chk(1);
    } FCT_QTEST_END();

    FCT_FINAL();
    return FCT_NUM_FAILED();
}

int
main(int argc, char *argv[]) {
    return _start_test(argc, argv);
}
