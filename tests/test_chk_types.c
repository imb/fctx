/*
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.
====================================================================
File: test_chk_types.c

*/

#include <float.h>
#include <math.h>
#include "fct.h"

/* My Own Type. */
typedef struct _point_t
{
    float x,y,z;
} point_t;

#define point_is_eq(p1, p2, ep) \
    ((int)(fabs(p1.x - p2.x) < ep)) &&\
    ((int)(fabs(p1.y - p2.y) < ep)) &&\
    ((int)(fabs(p1.z - p2.z) < ep))

#define point_chk_eq(p1, p2, ep) \
    fct_xchk(\
        point_is_eq(p1, p2, ep), \
        "failed point_is_equal:\n<Point x=%f y=%f z=%f>"\
        " !=\n<Point x=%f y=%f z=%f>",\
        p1.x, p1.y, p1.z, p2.x, p2.y, p2.z\
        );

#define point_is_neq(p1, p2, ep) \
    (!(int)(fabs(p1.x - p2.x) < ep)) ||\
    (!(int)(fabs(p1.y - p2.y) < ep)) ||\
    (!(int)(fabs(p1.z - p2.z) < ep))

#define point_chk_neq(p1, p2, ep) \
    fct_xchk(\
        point_is_neq(p1, p2, ep), \
        "failed point_chk_neq:\n<Point x=%f y=%f z=%f>"\
        " ==\n<Point x=%f y=%f z=%f>",\
        p1.x, p1.y, p1.z, p2.x, p2.y, p2.z\
        );


FCT_BGN()
{
    FCT_QTEST_BGN(chk_dbl_eq)
    {
        fct_chk_eq_dbl(6123.2313,6123.2313);
    }
    FCT_QTEST_END();

    FCT_QTEST_BGN(chk_dbl_neq)
    {
        fct_chk_neq_dbl(1.11111, 1.1);
    }
    FCT_QTEST_END();

    FCT_QTEST_BGN(chk_str_eq)
    {
        fct_chk_eq_str("a", "a");
        fct_chk_eq_str(NULL, NULL);
        fct_chk_eq_str("boo", "boo");
    }
    FCT_QTEST_END();

    FCT_QTEST_BGN(chk_neq_str)
    {
        fct_chk_neq_str("a", "b");
        fct_chk_neq_str(NULL, "b");
        fct_chk_neq_str("a", NULL);
    }
    FCT_QTEST_END();

    FCT_QTEST_BGN(chk_eq_istr)
    {
        fct_chk_eq_istr("mismatch", "misMatch");
        fct_chk_eq_istr("a", "a");
        fct_chk_eq_istr("A", "a");
        fct_chk_eq_istr(NULL, NULL);
    }
    FCT_QTEST_END();

    FCT_QTEST_BGN(chk_neq_istr)
    {
        fct_chk_neq_istr("mismatch", "misMatchLength");
        fct_chk_neq_istr("a", "b");
        fct_chk_neq_istr("A", "b");
        fct_chk_neq_istr(NULL, "b");
        fct_chk_neq_istr("A", NULL);
    }
    FCT_QTEST_END();


    FCT_QTEST_BGN(chk_my_point)
    {
        point_t point1 = {1.f, 2.f, 3.f};
        point_t point2 = {1.f, 2.f, 3.f};
        point_t point3 = {10.f, 20.f, 30.f};
        point_chk_eq(point1, point2, DBL_EPSILON);
        point_chk_neq(point1, point3, DBL_EPSILON);
    }
    FCT_QTEST_END();
}
FCT_END();
