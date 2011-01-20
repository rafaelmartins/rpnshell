ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = rpnshell

rpnshell_SOURCES = \
	src/main.c \
	src/rpn_stack.c \
	src/rpn_operators.c \
	src/rpn_stack.h \
	src/rpn_operators.h

rpnshell_CFLAGS = \
	$(AM_CFLAGS) \
	$(LIBEDIT_CFLAGS)

rpnshell_LDADD = \
	$(AM_LDADD) \
	$(LIBEDIT_LIBS)

EXTRA_DIST = bootstrap.sh
dist_doc_DATA = NEWS COPYING README AUTHORS
