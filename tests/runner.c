/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================
File: test_runner.c

This program can be used to run tests that are supposed to fail, and make sure
they supposed to fail with some reasonable number.

For example. Currently test_chk.exe is supposed to report 2 failures, which is
correct, but it if reports 1 or 3 failures then there is something wrong.

programs: test_runner.exe [program] [count]
*/

#include <stdlib.h>
#include <stdio.h>

/* System is a goofy way to do this, and we need to make sure we are able to
work on both windows and linux. So the following makes a system call and
returns the ACTUAL return value from the code. */
#ifdef _WIN32
#   define EXIT_STATUS(s)  (s)
#else
#   include <sys/wait.h>
#   define EXIT_STATUS(s)  WEXITSTATUS((s))
#endif

int
main(int argc, char *argv[])
{
    char *rv_str =NULL;
    int expected_rv =0;
    int rv =0;
    char *progname =NULL;

    if ( argc < 2 )
    {
        return EXIT_FAILURE;
    }
    progname = argv[1];
    rv_str = argv[2];
    expected_rv = atoi(rv_str);

    printf("RUNNER: starting '%s': expecting %d\n", progname, expected_rv);

    rv = EXIT_STATUS(system(progname));

    printf(
        "RUNNER: finished '%s'; expected %s, received %d\n",
        progname,
        rv_str,
        rv
    );
    return (rv == expected_rv) ?  (EXIT_SUCCESS) : (EXIT_FAILURE);
}
