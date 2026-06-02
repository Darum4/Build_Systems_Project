AC_INIT([Zetto Archiver], [1.0])
AC_PREREQ([2.69])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_PROG_CXX
AC_LANG([C++])

AX_CXX_COMPILE_STDCXX([23], [noext], [mandatory])

CXXFLAGS="$CXXFLAGS -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_FAST -D_FILE_OFFSET_BITS=64"

AC_CHECK_LIB([z], [compress], [], [AC_MSG_ERROR([zlib library not found!])])
AC_CHECK_HEADER([zlib.h], [], [AC_MSG_ERROR([zlib headers not found!])])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
