Execute a Subset of Tests Based on a Tag
========================================
 
  :Reference: https://blueprints.launchpad.net/fctest/+spec/execute-tag-tests
  :Version: $Revision$
  :Last Modified: $Date$
  :Author: Ian Blumel <ian DOT blumel at gmail DOT com>
  :Status: Active

--------
Overview
--------
 
Be able to execute some subset of tests based on a tag that was supplied for
each test. For instance you may have a set of tests that are tagged as
"critical".  These tests must always be executed, and can be run quickly to
confirm that the "basic" tests work out of the can. But if you have time, you
can also run _all_ the tests.
 
------------------
Current Workaround
------------------
 
The current workaround involves partioning the tests based on a series of
files. This only works if you want to form major groupings like "critical" and
"non-critical". It will involve creating 5 files: 3 source files and 2 header
files. You will have the following,
 
  1. "critical_tests.h": For all tests that must be run.
  1. "non_critical_tests.h": For all tests that we would like to run.
  1. "run_critical_tests.c": Executes all critical test.
  1. "run_non_critical_tests.c": Executes all non-critical tests.
  1. "run_all.c": Runs both critical and non-critical tests.
 
The trick here is in how you define your implemenation files. If you look at
the existing FCT "test_multi.c" as an example you will see you can do something
like this for, "run_critical.c",

  .. code-block:: c
 
    #include "fct.h" 
    FCT_BGN()
    {
    #include "test_multi_suite_a.h"
    #include "test_multi_suite_b.h"
    }
    FCT_END();
 
and then "run_all.c" would look something like this,

  .. code-block:: c
 
    #include "fct.h"
     
    FCT_BGN()
    {
    #include "test_multi_suite_a.h"
    #include "test_multi_suite_b.h"
    }
    FCT_END();
 
As you can see this is a tedious and clumsy way to break out your tests.
 
-------
Details
-------
 
There are two parts to using the "tags": first, we need to figure out how to
specify the tags on a test; second, we need to figure out how to "invoke" the
tags 
 

Specifying Tags on a Test
-------------------------
 
All tags will be specified as a comma-delimited list of tags associated with a
test. The only part that needs a little work is figuring out if we should
create a new macro for "inserting"  a tag on a test, or if we should add the
tag to the "test definition". 
 
  1. Create a new FCT_TAGTEST_BGN  macro, that takes an extra field for tags.
 
     .. code-block: c 

	  FCT_TAGTEST_BGN(test_strcmp, "critical,string")
	  {
	     char const *test_str  = "test_str";
	     fct_chk( strcmp(test_str, "test") != 0);
	     fct_chk( strcmp(test_str, "test_str") == 0);
	  }
	  FCT_TEST_END();
 
    - Pros:  Implementation is easy, because the code used to "skip" a test is
      within the FCT_TAGTEST_BGN macro. 
    - Cons:  Not very extensible, and FCT_TAGTEST_BGN  is starting to getting
      annoying to type. ;-)
 
 
  2. Adding a new FCT_TAG macro.
 
     .. code-block:: c
 
	  FCT_TEST_BGN(test_strcmp)
	  {  
		FCT_TAG("critical, string");
	     char const *test_str  = "test_str";
	     fct_chk( strcmp(test_str, "test") != 0);
	     fct_chk( strcmp(test_str, "test_str") == 0);
	  }
	  FCT_TEST_END();
 
 
     - Pros: Does not effect existing FCT_TEST_BGN  macro. Clearly marks out
       TAGing process.
     - Cons:  Implemenation is a bit tricker, and the  FCT_TAG  macro is not
       "Forced"  to be the first line?
 
 
  3. Add a generic "parametization"  of tests. I  am using "FCT_ATEST_BGN"
where the "A"  signals attributed. This option allows us to accept more
attributes in the future.

    .. code-block:: c
 
	  FCT_ATEST_BGN(test_strcmp, "tag=critical,string;author=Ian")
	  {
	     char const *test_str  = "test_str";
	     fct_chk( strcmp(test_str, "test") != 0);
	     fct_chk( strcmp(test_str, "test_str") == 0);
	  }
	  FCT_TEST_END();
 
 
    - Pros: Implemenation is easier, and the tagging process is extensible.
    - Cons:  Specifying parameters with ","  and ";"  could lead to errors. May
      be able to use some macro slicing to make it less error prone. 
 
So far I  perfer Option 3 but if do allow generic attributes, we should
consider that::
 
    "tag=critical" ";" "tag=string"
 
Is equivalent to::
 
    "tag=critical,string"
 
The first option lets you construct a set of parameters for a project based on
some project standards, as in,

.. code-block:: c
 
    #define CRIT_TAG  "tag=critical"
    #define STR_TAG "tag=string"
    #define AUTH_IB "author=ib"
    FCT_ATEST_BGN(test_strcmp, CRIT_TAG ";" STR_TAG ";" AUTH_IB)
 
This way you can reduce the chance of accidently mispelling "critical". 
 
Invoking from the Command Line
------------------------------
 
Currently I am thinking that if we use generic attributes we can get away with
something like::
 
    mytest.exe --run-attr=tag:critical,tag:string
 
which would run all tests that have a "tag" that is "critical" and all
attributes that have a tag that is a "string". You can mix and match this way
with something like::
 
  mytest.exe --run-attr=tag:critical,author:ib
 
which would run all critical tests writen by "ib".

