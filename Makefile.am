ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = foreign no-dist-gzip dist-bzip2

bin_PROGRAMS = rpnshell

rpnshell_SOURCES = src/main.c src/rpn_stack.c src/rpn_operators.c
noinst_HEADERS = src/rpn_stack.h src/rpn_operators.h

EXTRA_DIST = bootstrap.sh
dist_doc_DATA = ChangeLog NEWS COPYING README AUTHORS
DISTCLEANFILES = ChangeLog

