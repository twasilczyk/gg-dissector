AC_INIT([packet-gg], [1.0.0])

AM_INIT_AUTOMAKE()
AM_SILENT_RULES([yes])

AC_CONFIG_MACRO_DIR([m4])
AC_PREFIX_DEFAULT(/usr)

AC_CONFIG_HEADERS(config.h)

AC_CHECK_HEADERS([stdarg.h])

AC_DISABLE_STATIC

AC_PROG_CXX
AM_PROG_AR
AC_PROG_LIBTOOL

AC_CONFIG_FILES([
	Makefile
])

PKG_CHECK_MODULES(GLIB, [glib-2.0])

AC_PATH_PROG([WIRESHARK], [wireshark])
if test -z "$WIRESHARK"; then
	AC_MSG_ERROR([Wireshark not found])
fi
WIRESHARK_version=`$WIRESHARK -v | grep '^wireshark ' | head -n 1 | cut -d' ' -f 2`
WIRESHARK_includes="$includedir/wireshark"

CXXFLAGS="$CXXFLAGS -I$WIRESHARK_includes $GLIB_CFLAGS"
CXXFLAGS="$CXXFLAGS -D_U_=__attribute__\(\(unused\)\)"
CXXFLAGS="$CXXFLAGS -DXUSE_MTSAFE_API -fPIC -DPIC"
CXXFLAGS="$CXXFLAGS -DINET6 -Wpointer-arith -DXTHREADS -D_REENTRANT"
CXXFLAGS="$CXXFLAGS -DHAVE_CONFIG_H"
CXXFLAGS="$CXXFLAGS -Wall -Wextra -std=c++11"

AC_DEFINE([WS_MSVC_NORETURN], [], [Always empty])

plugindir="$libdir/wireshark/plugins/$WIRESHARK_version"
AC_SUBST([plugindir])

AC_OUTPUT
