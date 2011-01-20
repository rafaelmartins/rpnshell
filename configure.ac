AC_PREREQ(2.68)

AC_INIT([rpnshell], [0.1], [rafael@rafaelmartins.eng.br])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign no-dist-gzip dist-bzip2 subdir-objects])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AC_CONFIG_HEADERS([config.h])

LT_PREREQ([2.2.4])
LT_INIT

AC_PROG_CC_C99
AC_PROG_INSTALL

AX_LIB_READLINE
AS_IF([test "x$ax_cv_lib_readline" = "xno"], [
  AC_MSG_ERROR([no readline library found.])
])

AC_FUNC_MALLOC
for f in sqrtf pow; do
  AC_SEARCH_LIBS([$f], [m], , AC_MSG_ERROR([$f not found in -lm.]))
done

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
