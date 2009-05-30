# Specifications for all the TEST executables.
#
# ====================================================================
# Copyright (c) 2009 Ian Blumel.  All rights reserved.
# 
# This software is licensed as described in the file LICENSE, which
# you should have received as part of this distribution.  
# ====================================================================

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(FCT)
ENABLE_TESTING()

# ------------------------
# Configure Warning Levels
# ------------------------

IF (MSVC)
    # Warning Level 4, Treat all warnings as errors!
	SET(WARNINGS "/WX /W4 /Wp64")
ENDIF (MSVC)
IF (MINGW)
	SET(WARNINGS "-Wall -Wextra -W64bit")
ENDIF(MINGW)

SET(CMAKE_C_FLAGS 	"${CMAKE_C_FLAGS} ${WARNINGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNINGS}")


# --------
# Delegate
# --------
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(doc)
