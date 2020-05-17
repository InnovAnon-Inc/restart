AC_INIT([librestart], [0.0], [laurence.a.maddox@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 src/restart.pc
])

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE([use-submodules],
    AS_HELP_STRING([--enable-use-submodules], [Enable use submodules]))
AM_CONDITIONAL([USE_SUBMODULES], [test x"$enable_use_submodules" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])
#AC_CONFIG_SUBDIRS([glitter])

AC_CHECK_HEADERS([errno.h fcntl.h limits.h string.h unistd.h])
AC_CHECK_HEADERS([sys/select.h sys/time.h sys/types.h sys/wait.h])
AC_CHECK_HEADERS([glitter.h])

AC_CHECK_LIB([stdlib],[close,dup2,open,read,wait,waitpid,write])
AC_CHECK_LIB([stdlib],[gettimeofday,select,sleep])

##srcdir = @srcdir@
##LIBRESTART_LIBADD="`PATH=$(srcdir)src:$PATH librestart_config --libs`"
#LIBRESTART_LIBADD="`PATH=src:$PATH librestart_config --libs`"
#AC_SUBST(LIBRESTART_LIBADD)
#PKG_CHECK_MODULES(librestart,,,)
#AC_SUBST(PROJECT_RESTART_LIBS)
#AC_SUBST(PROJECT_RESTART_CFLAGS)

INNOVANON_WARNINGS([])

AC_OUTPUT
