AC_INIT([librestart], [0.0], [laurence.a.maddox@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_CONFIG_MACRO_DIR([m4])
AC_OUTPUT

AC_CHECK_HEADERS([errno.h fcntl.h limits.h string.h unistd.h])
AC_CHECK_HEADERS([sys/select.h sys/time.h sys/types.h sys/wait.h])
AC_CHECK_HEADERS([glitter.h])

AC_CHECK_LIB([stdlib],[close,dup2,open,read,wait,waitpid,write])
AC_CHECK_LIB([stdlib],[gettimeofday,select,sleep])
