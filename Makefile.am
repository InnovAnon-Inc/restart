# Install the pkg-config file.
pkgconfigdir = $(libdir)/@PACKAGE_NAME@/pkgconfig
pkgconfig_DATA = src/restart.pc
 
DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/restart.pc.in

#SUBDIRS = glitter src
SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

