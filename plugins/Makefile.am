#
# rpnshell: A RPN-based calculator to the command-line interface.
# Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
#
# This program can be distributed under the terms of the BSD License.
# See the file COPYING.
#

AM_CFLAGS = \
	$(all_includes)	\
	-I$(top_srcdir)/include

AM_LDFLAGS = \
	-avoid-version \
	-module \
	-shared \
	-export-dynamic

pkglib_LTLIBRARIES = \
	rpnshell_core.la \
	rpnshell_helpers.la

rpnshell_core_la_SOURCES = \
	core.c \
	$(top_srcdir)/include/plugin.h \
	$(top_srcdir)/include/rpn_stack.h

rpnshell_core_la_LIBADD = \
	$(top_builddir)/lib/librpnshell.la

rpnshell_helpers_la_SOURCES = \
	helpers.c \
	$(top_srcdir)/include/plugin.h \
	$(top_srcdir)/include/rpn_stack.h

rpnshell_helpers_la_LIBADD = \
	$(top_builddir)/lib/librpnshell.la
