#
# rpnshell: A RPN-based calculator to the command-line interface.
# Copyright (C) 2010-2011 Rafael G. Martins <rafaelmartins@gentoo.org>
#
# This program can be distributed under the terms of the BSD License.
# See the file COPYING.
#

bin_PROGRAMS = rpnshell
pkginclude_HEADERS = plugin.h

rpnshell_SOURCES = \
	main.c \
	plugins.c \
	plugins.h \
	$(top_srcdir)/lib/rpn_stack.h

rpnshell_CFLAGS = \
	$(AM_CFLAGS) \
	$(LIBEDIT_CFLAGS)\
	-I$(top_srcdir)/lib \
	-DPKGLIBDIR=\"@libdir@/@PACKAGE@\"

rpnshell_LDADD = \
	$(AM_LDADD) \
	$(LIBEDIT_LIBS) \
	$(top_builddir)/lib/librpnshell.la

