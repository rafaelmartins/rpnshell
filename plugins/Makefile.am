#
# rpnshell: A RPN-based calculator to the command-line interface.
# Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
#
# This program can be distributed under the terms of the BSD License.
# See the file COPYING.
#


### definitions ###

pkglib_LTLIBRARIES = \
	rpnshell_core.la \
	rpnshell_helpers.la


### sources ###

rpnshell_core_la_SOURCES = \
	core.c \
	$(top_srcdir)/src/plugin.h \
	$(top_srcdir)/src/rpn_stack.h

rpnshell_helpers_la_SOURCES = \
	helpers.c \
	$(top_srcdir)/src/plugin.h \
	$(top_srcdir)/src/rpn_stack.h


### cflags ###

AM_CFLAGS = \
	$(all_includes) \
	-I$(top_srcdir)/src


### ldflags ###

AM_LDFLAGS = \
	-avoid-version \
	-module \
	-shared \
	-export-dynamic

rpnshell_core_la_LIBADD = \
	$(top_builddir)/src/librpnshell.la

rpnshell_helpers_la_LIBADD = \
	$(top_builddir)/src/librpnshell.la
