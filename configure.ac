AC_PREREQ(2.62)

AC_INIT([rpnshell], [0.1], [rafael@rafaelmartins.eng.br])
AC_SUBST(PACKAGE_TARNAME)
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

LT_PREREQ([2.2.4])
LT_INIT

AC_PROG_CC_C99
AS_IF([test "x$ac_cv_prog_cc_c99" = "xno"], [
  AC_MSG_ERROR([no C99 compiler found.])
])

AX_LIB_READLINE
AS_IF([test "x$ax_cv_lib_readline" = "xno"], [
  AC_MSG_ERROR([no readline library found.])
])

for f in sqrtf powf; do
  AC_SEARCH_LIBS($f, m, , AC_MSG_ERROR([$f not found in -lm.]))
done

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
