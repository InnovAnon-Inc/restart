# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/restart.pc
 
DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/restart.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

