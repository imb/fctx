# Specifications for all the TEST executables.
#
# ====================================================================
# Copyright (c) 2009 Ian Blumel.  All rights reserved.
# 
# This software is licensed as described in the file LICENSE, which
# you should have received as part of this distribution.  
# ====================================================================

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

ADD_EXECUTABLE(test_basic test_basic.c)
ADD_EXECUTABLE(test_1suite test_1suite.c)

ADD_EXECUTABLE(test_count test_count.c)
ADD_EXECUTABLE(test_fail test_fail.c)
ADD_EXECUTABLE(test_kern test_kern.c)
ADD_EXECUTABLE(test_money test_money.c)
ADD_EXECUTABLE(test_multi test_multi.c)
ADD_EXECUTABLE(test_two_names test_two_names.c)

# TEST_BIG. This requires generating test_big.c before we can
# build test_big.exe. To generate test_big.c you need to compile
# and execute mkbigtest.c. Here is what is happening below,
#
#  1. First we say to build mkbigtest we need to compile mkbigtest.c
#  2. Then we say to build test_big you need to compile test_big.c
#  3. Then we say, well, to generate a test_big.c file you need to
#     run mkbigtest.
#  4. Finally we just make it obvious that to make your test_big you
#     need to make your mkbigtest. I tried to set a dependency on 
#     test_big.c, which seems more natural to me, but CMAKE could not
#     locate a target called "test_big.c".
ADD_EXECUTABLE(mkbigtest mkbigtest.c)
ADD_CUSTOM_COMMAND(
    OUTPUT test_big.c
    COMMAND mkbigtest
    DEPENDS mkbigtest 
    )	
ADD_EXECUTABLE(test_big test_big.c)

# -------
# TESTING 
# -------

ENABLE_TESTING()
ADD_TEST(run_test_basic test_basic)
ADD_TEST(run_test_1suite test_1suite)
ADD_TEST(run_test_count test_count)
ADD_TEST(run_test_kern test_kern)
ADD_TEST(run_test_money test_money)
ADD_TEST(run_test_multi test_multi)
ADD_TEST(run_test_two_names test_two_names)
ADD_TEST(run_test_big test_big)

# The following tests confirm that failure happens.
ADD_TEST(run_test_fail test_fail)
SET_TESTS_PROPERTIES(run_test_fail PROPERTIES WILL_FAIL TRUE) 
