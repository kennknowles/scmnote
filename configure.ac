AC_INIT( src/ScmNote.cpp )

AM_INIT_AUTOMAKE(scmnote, 0.0.2)

AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# guile flag setup
GUILE_FLAGS
CXXFLAGS="$CXXFLAGS $GUILE_CFLAGS"
LIBS="$LIBS $GUILE_LDFLAGS"

AC_DEFINE(LDATADIR, "data",
	[The path from TOP_SRCDIR to data _in the source tree_])
AC_DEFINE(LCONFDIR, "etc",
	[The path from TOP_SRCDIR to conf _in the source tree_])
AC_DEFINE(SRCDIR, "src",
	[The path from TOP_SRCDIR to src _in the source tree_])

AC_SUBST(CXXFLAGS)
AC_SUBST(LIBS)

AC_OUTPUT( \
		Makefile \
		src/Makefile \
		man/Makefile \
		examples/Makefile \
		man/scmnote.1 \
		data/Makefile )

echo "
Configuration successful, now do make && make install to install RCRCTF
to $prefix
"

