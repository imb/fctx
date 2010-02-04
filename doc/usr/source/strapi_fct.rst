==================
fctstr: String API
==================

.. module:: fctstr
   :platform: Unix, Windows
   :synopsis: Basic string API to support unit testing.

.. versionadded:: 1.2
   API for string operations that you may encounter during unit testing.

Introduction
------------

Provides an API for common string operations that you may encounter during unit
testing. This module will grow over time.

String Functions
----------------

.. cfunction:: fctstr_clone(s)

        Allocates new memory, and copies the contents of *s* into the result.
        Callee should use the standard C Runtime Library's *free* function to
        clean up the memory.

.. cfunction:: fctstr_eq(s1,s2)

        Returns a non-zero (TRUE) if *s1* and *s2* are equal. Unlike the
        standard strcmp function, this function can handle NULL values. This
        function will also quit the moment one of the strings is unequal. If
        *s1* and *s2* are NULL, this function will return non-zero (TRUE)
        value. See :cfunc:`fctstr_ieq` for a case-insenstive string compare.

.. cfunction:: fctstr_ieq(s1,s2) 
         
        Performs a case insensitve string compare, see :cfunc:`fctstr_eq` for
        more details.
