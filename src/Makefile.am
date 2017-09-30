AM_CPPFLAGS = -D__STDC_INT64__

SUBDIRS = ../glitter
AM_CPPFLAGS += -I $(top_srcdir)/glitter/src

LIBRESTART_LIBADD =

lib_LTLIBRARIES = librestart.la
include_HEADERS = restart.h
librestart_la_SOURCES = restart.c
librestart_la_LIBADD = $(LIBRESTART_LIBADD)
