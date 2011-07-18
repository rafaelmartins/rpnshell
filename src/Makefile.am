#
# rpnshell: A RPN-based calculator to the command-line interface.
# Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
#
# This program can be distributed under the terms of the BSD License.
# See the file COPYING.
#


### definitions ###

# instalable headers
pkginclude_HEADERS = \
	plugin.h \
	rpn_stack.h

# binary
bin_PROGRAMS = rpnshell

# library
lib_LTLIBRARIES = librpnshell.la


### sources ###

# binary
rpnshell_SOURCES = \
	rpnshell.c \
	plugins.c \
	plugins.h \
	rpn_stack.h

# library
librpnshell_la_SOURCES = \
	rpn_stack.c \
	rpn_stack.h


### cflags ###

# binary
rpnshell_CFLAGS = \
	$(AM_CFLAGS) \
	$(LIBEDIT_CFLAGS) \
        -I$(top_srcdir) \
	-DPKGLIBDIR=\"@libdir@/@PACKAGE@\"


### ldflags ###

# binary
rpnshell_LDADD = \
	$(AM_LDADD) \
	$(LIBEDIT_LIBS) \
	librpnshell.la

# library
librpnshell_la_LDFLAGS = \
	$(AM_LDADD) \
	-version-info $(LT_VERSION_INFO)

