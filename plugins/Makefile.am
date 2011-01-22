AM_CFLAGS = $(all_includes) -I$(top_srcdir)/src -I$(top_srcdir)/lib
AM_LDFLAGS = -avoid-version -module -shared -export-dynamic

pkglib_LTLIBRARIES = \
	rpnshell_core.la \
	rpnshell_helpers.la

rpnshell_core_la_SOURCES = \
	core.c \
	$(top_srcdir)/src/plugin.h \
	$(top_srcdir)/lib/rpn_stack.h

rpnshell_helpers_la_SOURCES = \
	helpers.c \
	$(top_srcdir)/src/plugin.h \
	$(top_srcdir)/lib/rpn_stack.h

