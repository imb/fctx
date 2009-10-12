/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================

File: test_clp.c

Runs through tests for the command line parser.
*/

#include "fct.h"

FCT_BGN()
{
    /* Run through a basic configuration and parse operations. */

    /* Test Data */
    fct_clp_t clp;
    fct_clo_t options[] =
    {
        {"--help",
            "-h",
            FCT_CLO_STORE_TRUE,
            "Shows this message",
            NULL},
        {"--output",
         NULL,
         FCT_CLO_STORE_VALUE,
         "Name of file to store output.",
         NULL
        },
        FCT_CLO_NULL
    };

    FCT_FIXTURE_SUITE_BGN(clp__parse_scenarios)
    {
        FCT_SETUP_BGN()
        {
            fct_clp__init(&clp, options);
        }
        FCT_SETUP_END();

        FCT_TEARDOWN_BGN()
        {
            fct_clp__final(&clp);
        }
        FCT_TEARDOWN_END();

        FCT_TEST_BGN(initialization)
        {
            fct_chk_eq_int( fct_clp__num_clo(&clp), 2);
        }
        FCT_TEST_END();

        FCT_TEST_BGN(parse_nothing)
        {
            char *argv[] = {"program.exe" };
            int argc =1;

            fct_clp__parse(&clp, argc, argv);

            fct_chk( !fct_clp__is(&clp, "--help") );
            fct_chk( !fct_clp__is(&clp, "--output") );
        }
        FCT_TEST_END();


        FCT_TEST_BGN(parse_store_true)
        {
            char *argv[] = {"program.exe", "--help"};
            int argc =2;

            fct_clp__parse(&clp, argc, argv);

            fct_chk( fct_clp__is(&clp, "--help") );
            fct_chk( !fct_clp__is(&clp, "--output") );
        }
        FCT_TEST_END();


        FCT_TEST_BGN(parse_store_value__with_2nd_arg)
        {
            char *argv[] = {"program.exe", "--output", "foo"};
            int argc =3;

            fct_clp__parse(&clp, argc, argv);

            fct_chk( !fct_clp__is(&clp, "--help") );
            fct_chk( fct_clp__is(&clp, "--output") );
            fct_chk_eq_str(fct_clp__value(&clp, "--output"), "foo");
        }
        FCT_TEST_END();


        FCT_TEST_BGN(parse_store_value__with_equals)
        {
            char *argv[] = {"program.exe", "--output=foo"};
            int argc =2;

            fct_clp__parse(&clp, argc, argv);

            fct_chk( !fct_clp__is(&clp, "--help") );
            fct_chk( fct_clp__is(&clp, "--output") );
            fct_chk_eq_str(fct_clp__value(&clp, "--output"), "foo");
        }
        FCT_TEST_END();


        FCT_TEST_BGN(parse_store_value__with_equals_but_no_value)
        {
            char *argv[] = {"program.exe", "--output="};
            char const *output_value =NULL;
            int argc =2;

            fct_clp__parse(&clp, argc, argv);

            fct_chk( !fct_clp__is(&clp, "--help") );
            fct_chk( fct_clp__is(&clp, "--output") );
            output_value = fct_clp__value(&clp, "--output");
            fct_chk_eq_str(output_value, "foo");
        }
        FCT_TEST_END();


        FCT_TEST_BGN(parse_store_value__without_2nd_arg)
        {
            char *argv[] = {"program.exe", "--output"};
            int argc =2;

            fct_clp__parse(&clp, argc, argv);

            fct_chk( !fct_clp__is(&clp, "--help") );
            fct_chk( fct_clp__is(&clp, "--output") );
        }
        FCT_TEST_END();


        FCT_TEST_BGN(parse__check_for_invalid_value)
        {
            char *argv[] = {"program.exe", "--output"};
            int argc =2;

            fct_clp__parse(&clp, argc, argv);

            fct_chk( !fct_clp__is(&clp, "--booga") );
            fct_chk( fct_clp__value(&clp, "--booga") == NULL );
        }
        FCT_TEST_END();


        FCT_TEST_BGN(parse_store_value__with_multiple_args)
        {
            char *argv[] = {"program.exe", "--output", "foo", "--help"};
            int argc =4;

            fct_clp__parse(&clp, argc, argv);

            fct_chk( !fct_clp__is(&clp, "--help") );
            fct_chk( fct_clp__is(&clp, "--output") );
            fct_chk_eq_str(fct_clp__value(&clp, "--output"), "foo");
        }
        FCT_TEST_END();


        FCT_TEST_BGN(parse_store_value__with_multiple_args_diff_order)
        {
            char *argv[] = {"program.exe",  "--help", "--output", "foo"};
            int argc =4;

            fct_clp__parse(&clp, argc, argv);

            fct_chk( !fct_clp__is(&clp, "--help") );
            fct_chk( fct_clp__is(&clp, "--output") );
            fct_chk_eq_str(fct_clp__value(&clp, "--output"), "foo");
        }
        FCT_TEST_END();

    }
    FCT_FIXTURE_SUITE_END();


}
FCT_END();
