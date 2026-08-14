# Define include headers to install in $(prefix)/include
include_HEADERS = muscalnc.h

# Define executable binaries to install in $(prefix)/bin
bin_PROGRAMS = muscalnc_query muscalnc_surface build_kdtree query_kdtree

# Define shared/static libraries to install in $(prefix)/lib
lib_LTLIBRARIES = libmuscalnc.la

# ------------------------------------------------------------------------------
# Library Definition
# ------------------------------------------------------------------------------

# Sources for the shared/static library
libmuscalnc_la_SOURCES = \
	muscalnc.c \
	muscalnc_dataset.c \
	muscalnc_util.c \
	um_netcdf.c \
	cJSON.c \
	kdtree_util.c

# Include path and flags for compiling the library
libmuscalnc_la_CPPFLAGS = -I$(top_srcdir) -I$(prefix)/include -DDYNAMIC_LIBRARY

# Linker flags and libraries for libmuscalnc
libmuscalnc_la_LDFLAGS = -version-info 1:0:0 -L$(prefix)/lib
libmuscalnc_la_LIBADD = -lm $(LIBS)

# ------------------------------------------------------------------------------
# Executables Definitions
# ------------------------------------------------------------------------------

AM_CPPFLAGS = -I$(top_srcdir) -I$(prefix)/include
AM_LDFLAGS = -L$(prefix)/lib

# muscalnc_query links against our Libtool library
muscalnc_query_SOURCES = muscalnc_query.c
muscalnc_query_LDADD = libmuscalnc.la -lm $(LIBS)

# muscalnc_surface links against our Libtool library
muscalnc_surface_SOURCES = muscalnc_surface.c
muscalnc_surface_LDADD = libmuscalnc.la -lm $(LIBS)

# build_kdtree helper
build_kdtree_SOURCES = build_kdtree.c kdtree_util.c
build_kdtree_LDADD = -lm $(LIBS)

# query_kdtree helper
query_kdtree_SOURCES = query_kdtree.c kdtree_util.c
query_kdtree_LDADD = -lm $(LIBS)

