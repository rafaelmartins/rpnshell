AM_CFLAGS = $(all_includes) -I$(top_srcdir)/src

pkglib_LTLIBRARIES = rpnshell_core.la

rpnshell_core_la_SOURCES = core.c $(top_srcdir)/src/plugin.h
rpnshell_core_la_LDFLAGS = -avoid-version -module -shared -export-dynamic

