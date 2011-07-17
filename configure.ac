#
# rpnshell: A RPN-based calculator to the command-line interface.
# Copyright (C) 2010-2011 Rafael G. Martins <rafael@rafaelmartins.eng.br>
#
# This program can be distributed under the terms of the BSD License.
# See the file COPYING.
#


AC_PREREQ(2.68)

AC_INIT([rpnshell], [0.1], [rafael@rafaelmartins.eng.br])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign no-dist-gzip dist-bzip2 subdir-objects])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AC_CONFIG_HEADERS([config.h])

LT_PREREQ([2.2.4])
LT_INIT

AC_MSG_CHECKING([for mercurial tip])
if test -d "${ac_top_srcdir:-.}/.hg"; then
  if test "x`hg id -t -R ${ac_top_srcdir:-.}`" = "xtip"; then
    HGTIP=`hg id -i -R ${ac_top_srcdir:-.}`
  fi
fi
if test -z "$HGTIP"; then
  AC_MSG_RESULT([no])
else
  AC_MSG_RESULT([$HGTIP])
  AC_DEFINE_UNQUOTED([HGTIP], ["$HGTIP"],
    [the changeset most recently added to the mercurial repository]
  )
fi

AC_PROG_CC_C99
AS_IF([test "x$ac_cv_prog_cc_c99" = "xno"], [
  AC_MSG_ERROR([no C99 compiler found.])
])

for f in sqrtf pow; do
  AC_SEARCH_LIBS([$f], [m], , AC_MSG_ERROR([$f not found in -lm.]))
done

AC_SEARCH_LIBS([dlopen], [dl dld], [], [
  AC_MSG_ERROR([unable to find the dlopen() function])
])

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LIBEDIT], [libedit])

AC_SUBST([lt_cv_objdir])

AC_CONFIG_FILES([Makefile include/Makefile lib/Makefile plugins/Makefile src/Makefile rpnshell.pc])
AC_OUTPUT

if test -z "$HGTIP"; then
  MY_PACKAGE_STRING="$PACKAGE_STRING"
else
  MY_PACKAGE_STRING="$PACKAGE_STRING/$HGTIP"
fi

echo "
	==== ${MY_PACKAGE_STRING} ====
	
	prefix:      ${prefix}
	exec_prefix: ${exec_prefix}
	bindir:      ${bindir}
	
	compiler:    ${CC}
	cflags:      ${CFLAGS}
	ldflags:     ${LDFLAGS}
"

