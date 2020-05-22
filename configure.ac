AC_INIT([librestart], [1.0], [InnovAnon-Inc@protonmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 src/librestart.pc
])

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE([use-submodules],
    AS_HELP_STRING([--enable-use-submodules], [Enable use submodules]))
AM_CONDITIONAL([USE_SUBMODULES], [test x"$enable_use_submodules" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])

AC_CHECK_HEADERS([errno.h fcntl.h limits.h string.h unistd.h])
AC_CHECK_HEADERS([sys/select.h sys/time.h sys/types.h sys/wait.h])
#AC_CHECK_HEADERS([glitter.h])

AC_CHECK_LIB([stdlib],[close,dup2,open,read,wait,waitpid,write])
AC_CHECK_LIB([stdlib],[gettimeofday,select,sleep])

PKG_CHECK_MODULES([GLITTER],[glitter],,)

INNOVANON_WARNINGS([])

AC_OUTPUT

