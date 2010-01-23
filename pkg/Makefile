# Simple makefile for building the package contents. Trying to keep 
# this to minimal requirements.
#
# The distribution builder isn't super fancy right now, and it is tied
# to Linux. In the future, I may re-write this in terms of CMAKE, so
# it can be used cross platform.
#
# ====================================================================
# Copyright (c) 2009 Ian Blumel.  All rights reserved.
# 
# This software is licensed as described in the file LICENSE, which
# you should have received as part of this distribution.  
# ====================================================================

VERSION_SHORT=1.2
VERSION=$(VERSION_SHORT).0
BRANCH=lp:/fctest/1.1
SRCPACK=fctx-src-${VERSION}.tar.gz
DOCPACK=fctx-doc-${VERSION}
DIST_DIR=dist

# Set the passphrase once with a command like:
#   	export PP="\"silly passphrase\"" 
SIGN=gpg --passphrase ${PP} --armour --sign --detach-sign

all: \
     ${DIST_DIR}/ChangeLog \
     ${DIST_DIR}/ChangeLog.asc \
     ${DIST_DIR}/${DOCPACK}.tar.gz \
     ${DIST_DIR}/${DOCPACK}.tar.gz.asc \
     ${DIST_DIR}/${DOCPACK}-WEB.tar.gz \
     ${DIST_DIR}/fct.h \
     ${DIST_DIR}/fct.h.asc \
     ${DIST_DIR}/NEWS \
     ${DIST_DIR}/NEWS.asc \
     ${DIST_DIR}/README \
     ${DIST_DIR}/README.asc \
     ${DIST_DIR}/${SRCPACK} \
     ${DIST_DIR}/${SRCPACK}.asc \

.PHONY: all clean sign doc help

help:
	@echo "Simple package builder. To use this effectively you first"
	@echo "need to set your PP environment variable to be your passphrase."
	@echo "Make sure you quote the environment variable properly. Next you"
	@echo "can run something like"
	@echo "   make clean all"

${DIST_DIR}:
	mkdir $@

${DIST_DIR}/${SRCPACK}: ${DIST_DIR}
	bzr export $@ ${BRANCH}

${DIST_DIR}/${SRCPACK}.asc: ${DIST_DIR}/${SRCPACK}
	${SIGN} $?

${DIST_DIR}/README: ${DIST_DIR}
	cp ../README ${DIST_DIR}/README

${DIST_DIR}/README.asc: ${DIST_DIR}/README
	${SIGN} $?

${DIST_DIR}/fct.h: ${DIST_DIR} ../include/fct.h
	cp ../include/fct.h ${DIST_DIR}/fct.h

${DIST_DIR}/fct.h.asc: ${DIST_DIR}/fct.h
	${SIGN} $?

# TODO: Upgrade BZR to get the --gnu-changelog option.
${DIST_DIR}/ChangeLog: ${DIST_DIR}
	bzr log -v --long > $@

${DIST_DIR}/ChangeLog.asc: ${DIST_DIR}/ChangeLog
	${SIGN} $?

${DIST_DIR}/NEWS: ${DIST_DIR}
	cp ../NEWS ${DIST_DIR}/NEWS

${DIST_DIR}/NEWS.asc: ${DIST_DIR}/NEWS
	${SIGN} $? 

${DIST_DIR}/${DOCPACK}.tar.gz: ${DIST_DIR} 
	make -C ../doc/usr html linkcheck \
	    VERSION=$(VERSION_SHORT) \
	    RELEASE=$(VERSION)
	[ -d ../doc/usr/build/${DOCPACK} ] && \
             rm -rf ../doc/usr/build/${DOCPACK} || \
             echo "pass"
	cp -r ../doc/usr/build/html ../doc/usr/build/${DOCPACK}
	tar -C ../doc/usr/build -cvvf ${DIST_DIR}/${DOCPACK}.tar ${DOCPACK}
	gzip ${DIST_DIR}/${DOCPACK}.tar

${DIST_DIR}/${DOCPACK}-WEB.tar.gz: ${DIST_DIR} 
	make -C ../doc/usr html_web linkcheck \
	    VERSION=$(VERSION_SHORT) \
	    RELEASE=$(VERSION)
	[ -d ../doc/usr/build/${DOCPACK}-WEB ] && \
             rm -rf ../doc/usr/build/${DOCPACK}-WEB || \
             echo "pass"
	cp -r ../doc/usr/build/html ../doc/usr/build/${DOCPACK}-WEB
	tar -C ../doc/usr/build -cvvf ${DIST_DIR}/${DOCPACK}-WEB.tar ${DOCPACK}-WEB
	gzip ${DIST_DIR}/${DOCPACK}-WEB.tar


${DIST_DIR}/${DOCPACK}.tar.gz.asc: ${DIST_DIR}/${DOCPACK}.tar.gz
	${SIGN} $?

# For easier documentation generation.
doc: ${DIST_DIR}/${DOCPACK}.tar.gz \
     ${DIST_DIR}/${DOCPACK}-WEB.tar.gz

cleandoc: 
	[ -f ${DIST_DIR}/${DOCPACK}.tar.gz ] && \
              rm -f ${DIST_DIR}/${DOCPACK}.tar.gz || \
              echo "${DIST_DIR}/${DOCPACK}.tar.gz does not exist"
	[ -f ${DIST_DIR}/${DOCPACK}-WEB.tar.gz ] && \
              rm -f ${DIST_DIR}/${DOCPACK}-WEB.tar.gz || \
              echo "${DIST_DIR}/${DOCPACK}-WEB.tar.gz does not exist"


clean: cleandoc
	rm -rf ${DIST_DIR}

.phony: clean cleandoc doc
