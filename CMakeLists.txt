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
    IF (MSVC80)
        # 64 bit warning flags are only really used in MSVC80.
	SET(WARNINGS "/WX /W4 /Wp64")
    ELSE()
        SET(WARNINGS "/WX /W4")
    ENDIF(MSVC90)
ENDIF (MSVC)
IF (CMAKE_COMPILER_IS_GNUCC)
	SET(WARNINGS "-Wall -Wextra")
ENDIF()

SET(CMAKE_C_FLAGS 	"${CMAKE_C_FLAGS} ${WARNINGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNINGS}")


# --------
# Delegate
# --------

ADD_SUBDIRECTORY(doc)
ADD_SUBDIRECTORY(include)
ADD_SUBDIRECTORY(tests)

# ---------
# Packaging
# ---------

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "fctest")
SET(CPACK_PACKAGE_VENDOR "wildbear")
SET(CPACK_GENERATOR "TGZ")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE
    ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
SET(CPACK_PACKAGE_VERSION_MAJOR 1)
SET(CPACK_PACKAGE_VERSION_MINOR 1)
SET(CPACK_PACKAGE_VERSION_PATCH 0)

INCLUDE(CPack)


