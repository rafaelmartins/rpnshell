#
# rpnshell: A RPN-based calculator to the command-line interface.
# Copyright (C) 2010-2011 Rafael G. Martins <rafaelmartins@gentoo.org>
#
# This program can be distributed under the terms of the BSD License.
# See the file COPYING.
#

lib_LTLIBRARIES = librpnshell.la

librpnshell_la_SOURCES = \
	rpn_stack.c \
	$(top_srcdir)/include/rpn_stack.h

librpnshell_la_CFLAGS = \
	$(AM_CFLAGS) \
	-I$(top_srcdir)/include

librpnshell_la_LDFLAGS = \
	$(AM_LDADD) \
	-version-info 0:0:0

