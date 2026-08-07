# Autoconf/automake file

objects = um_netcdf.o muscalnc_dataset.o muscalnc_util.o cJSON.o kdtree_util.o

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS} ${CPPFLAGS} -I$(prefix)/include
AM_LDFLAGS = ${LDFLAGS} -L$(prefix)/lib ${LIBS} -lm


TARGETS = muscalnc_surface muscalnc_query libmuscalnc.a libmuscalnc.so build_kdtree query_kdtree

all: $(TARGETS)

install:
	mkdir -p ${prefix}
	mkdir -p ${prefix}/lib
	mkdir -p ${prefix}/include
	mkdir -p ${prefix}/bin
	cp libmuscalnc.so ${prefix}/lib
	cp libmuscalnc.a ${prefix}/lib
	cp muscalnc.h ${prefix}/include
	cp muscalnc_query ${prefix}/bin

clean:
	rm -rf $(TARGETS)
	rm -rf *.o

libmuscalnc.a: muscalnc_static.o muscalnc_dataset.o muscalnc_util.o um_netcdf.o cJSON.o kdtree_util.o
	$(AR) rcs $@ $^

libmuscalnc.so: muscalnc.o muscalnc_dataset.o muscalnc_util.o  um_netcdf.o cJSON.o kdtree_util.o
	$(CC) -shared $(AM_FCFLAGS) -o libmuscalnc.so $^ $(AM_LDFLAGS)

muscalnc.o: muscalnc.c
	$(CC) -fPIC -DDYNAMIC_LIBRARY -o $@ -c $^ $(AM_CFLAGS)

muscalnc_static.o: muscalnc.c
	$(CC) -o $@ -c $^ $(AM_CFLAGS)

$(objects): %.o: %.c
	$(CC) -fPIC -DDYNAMIC_LIBRARY $(AM_CFLAGS) -o $@ -c $^

muscalnc_query.o: muscalnc_query.c
	$(CC) $(AM_CFLAGS) -o $@ -c $^

muscalnc_query : muscalnc_query.o libmuscalnc.a
	$(CC) -o $@ $^ $(AM_LDFLAGS)

muscalnc_surface.o: muscalnc_surface.c
	$(CC) $(AM_CFLAGS) -o $@ -c $^

muscalnc_surface : muscalnc_surface.o libmuscalnc.a
	$(CC) -o $@ $^ $(AM_LDFLAGS)

build_kdtree.o: build_kdtree.c
	$(CC) $(AM_CFLAGS) -o $@ -c $^

build_kdtree: build_kdtree.o kdtree_util.o
	$(CC) -o $@ $^ $(AM_LDFLAGS)

query_kdtree.o: query_kdtree.c
	$(CC) $(AM_CFLAGS) -o $@ -c $^

query_kdtree: query_kdtree.o kdtree_util.o
	$(CC) -o $@ $^ $(AM_LDFLAGS)

