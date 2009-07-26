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

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#ifdef _WIN32
#	include <direct.h>
#endif


/* System is a goofy way to do this, and we need to make sure we are able to
work on both windows and linux. So the following makes a system call and
returns the ACTUAL return value from the code. */
#ifdef _WIN32
#   define EXIT_STATUS(s)  (s)
#else
#   include <sys/wait.h>
#   define EXIT_STATUS(s)  WEXITSTATUS((s))
#endif

/* Program Name is sent to use by CMAKE, which uses a *nix style forward
slashes for its naming. If we are windows, the system call will fail,
so we shall convert it to a native path right here right now. This
function does the right thing on the right platform. */
#ifdef _WIN32
static void
to_native_inplace(char *progname)
{
    char *cp;
    for ( cp = progname; *cp != '\0'; ++cp )
    {
        if ( *cp == '/' )
        {
            *cp = '\\';
        }
    }
}
#else
#define to_native_inplace(progname)
#endif



#ifdef _WIN32
/* On a window's system, we have switch our program into the correct
directory before we run it. Especially if we are configured within
a Visual Studio (mulit-configuration) environment. In those cases
CMAKE will not set up the paths correctly. The following 'run'
command will run the program and return the exit code of the
program back to the client. */
static void
dirname(char const *path, char *dirname, size_t dirname_len)
{
    size_t path_len =0;
    size_t path_i =0;
    assert( path != NULL );
    assert( dirname != NULL);
    /* Walk from the end until we hit on the window's seperator.
    Assume that path is a full, absolute path. */
    path_len = strlen(path);
    for ( path_i=path_len-1; path_i != 0; --path_i )
    {
        if (path[path_i] == '\\' )
        {
            break;
        }
    }
    if ( dirname_len < path_i )
    {
        assert( dirname_len > path_i );
        fprintf(stderr, "abort, dirname unable to parse path");
        exit(EXIT_FAILURE);
    }
    strncpy(dirname, path, path_i);
}


static int
run(char *arg0, char *progname)
{
#define MAX_DIR 256
    char dir[MAX_DIR] = {'\0'};

    assert( arg0 != NULL );
    assert( progname != NULL);
    to_native_inplace(arg0);
    to_native_inplace(progname);
    dirname(arg0, dir, MAX_DIR);
    _chdir(dir);
    return EXIT_STATUS(system(progname));
#undef MAX_DIR
}
#else
static int
run(char const *arg0, char const *progname)
{
    (void)arg0;
    return EXIT_STATUS(system(progname));
}
#endif


int
main(int argc, char *argv[])
{
    char *rv_str =NULL;
    int expected_rv =0;
    int rv =0;
    char *progname =NULL;

    /* The worlds worst command line parser. ;-) */
    assert( argc == 3 && "Can only accept three arguments!");
    (void)argc;

    progname = argv[1];
    rv_str = argv[2];
    expected_rv = atoi(rv_str);

    printf("RUNNER: starting '%s': expecting %d\n", progname, expected_rv);

    rv = run(argv[0], progname);

    printf(
        "RUNNER: finished '%s'; expected %s, received %d\n",
        progname,
        rv_str,
        rv
    );
    return (rv == expected_rv) ?  (EXIT_SUCCESS) : (EXIT_FAILURE);
}
