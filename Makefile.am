#
# rpnshell: A RPN-based calculator to the command-line interface.
# Copyright (C) 2010-2011 Rafael G. Martins <rafaelmartins@gentoo.org>
#
# This program can be distributed under the terms of the BSD License.
# See the file COPYING.
#

SUBDIRS = plugins

ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = $(all_includes) -DPKGLIBDIR=\"@libdir@/@PACKAGE@\"

bin_PROGRAMS = rpnshell

rpnshell_SOURCES = \
	src/main.c \
	src/rpn_stack.c \
	src/rpn_operators.c \
	src/plugins.c \
	src/plugins.h \
	src/rpn_stack.h \
	src/rpn_operators.h

rpnshell_CFLAGS = \
	$(AM_CFLAGS) \
	$(LIBEDIT_CFLAGS)

rpnshell_LDADD = \
	$(AM_LDADD) \
	$(LIBEDIT_LIBS)

EXTRA_DIST = bootstrap.sh
