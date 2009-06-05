================
FCT Initializers
================

.. module:: FCT
   :platform: Unix, Windows
   :synopsis: Begin and End your test framework.

Overview 
--------

Every FCTest collection needs to be wrapped by two functions :cfunc:`FCT_BGN` 
and :cfunc:`FCT_END`.

Functions
---------

.. cfunction:: FCT_BGN()

	Initializes your test framework. Every test program needs to begin with
	this declaration.

.. cfunction:: FCT_END()

	Finalizes your test framwork. Every test program neesd to end with this
	declaration.