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
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

MACRO(TO_CPP _NAME_) 
	ADD_CUSTOM_COMMAND(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_}.cpp
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${_NAME_}.c ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_}.cpp
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${_NAME_}.c
		)
	ADD_CUSTOM_TARGET(
		generate_${_NAME_}_cpp
       		DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_}.cpp
		) 
	SET_SOURCE_FILES_PROPERTIES(
		${CMAKE_CURRENT_BINARY_DIR}/${_NAME_}.cpp 
		PROPERTIES GENERATED 1
		)
ENDMACRO(TO_CPP)

MACRO(TEST_CPP_VERSION _NAME_)
    TO_CPP(${_NAME_})
    ADD_EXECUTABLE(${_NAME_}_cpp ${CMAKE_CURRENT_BINARY_DIR}/${_NAME_}.cpp)
    ADD_TEST(run_${_NAME_}_cpp ${_NAME_}_cpp)
ENDMACRO(TEST_CPP_VERSION)


SET(SIMPLE_TESTS test_1suite
                 test_basic
		 test_call_teardown
		 test_count
                 test_money
		 test_multi_old_style
		 test_quick_test
		 test_two_names
	)	

FOREACH( PROGRAM ${SIMPLE_TESTS}) 
	ADD_EXECUTABLE(${PROGRAM} ${PROGRAM}.c)
ENDFOREACH(PROGRAM)

# This requires more than one file and doesn't fall under the "test simple"
# category.
ADD_EXECUTABLE(
	test_multi 
	test_multi.c test_multi_suite1.c test_multi_with_fixtures_suite2.c
	)

# This one will always fail.
ADD_EXECUTABLE(test_fail test_fail.c)

# This utilty can be used to run tests that are supposed to return non-zero
# values. Some tests are supposed to report failures like: 2 errors.
ADD_EXECUTABLE(runner runner.c)

# This one has the potential for always failing. I may start to add an option
# to let tests pass if they fail. ;-)
ADD_EXECUTABLE(test_chk test_chk.c)

ADD_DEPENDENCIES(test_chk runner)


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

FOREACH( PROGRAM ${SIMPLE_TESTS}) 
  ADD_TEST(run_${PROGRAM} ${PROGRAM})
  TEST_CPP_VERSION(${PROGRAM})
ENDFOREACH(PROGRAM)

ADD_TEST(run_test_big test_big)
ADD_TEST(run_test_call_teardown test_call_teardown)

TO_CPP(test_multi)
TO_CPP(test_multi_suite1)
TO_CPP(test_multi_with_fixtures_suite2)
ADD_EXECUTABLE(test_multi_cpp 
	${CMAKE_CURRENT_BINARY_DIR}/test_multi.cpp 
	${CMAKE_CURRENT_BINARY_DIR}/test_multi_suite1.cpp
	${CMAKE_CURRENT_BINARY_DIR}/test_multi_with_fixtures_suite2.cpp
	)
ADD_TEST(run_test_multi_cpp test_multi_cpp)

# The following tests confirm that failure happens.
ADD_TEST(run_test_fail test_fail)
SET_TESTS_PROPERTIES(run_test_fail PROPERTIES WILL_FAIL TRUE) 

ADD_TEST(run_test_chk ${CMAKE_CURRENT_BINARY_DIR}/runner 
                      ${CMAKE_CURRENT_BINARY_DIR}/test_chk 
                      2)

