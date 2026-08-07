# Autoconf/automake file

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_FCFLAGS = ${FCFLAGS}
AM_LDFLAGS = ${LDFLAGS}

all:
if WITH_MUSCALNC_LARGEDATA_DIR
	echo "USING WITH_MUSCALNC_LARGEDATA_DIR in muscalnc"
else
	echo "NOT USING WITH_MUSCALNC_LARGEDATA_DIR in muscalnc"
	if [ ! -d "muscalnc" ] && [ ! -L "muscalnc" ]; then \
		./make_data_files.py; \
	fi 
endif

install:
if WITH_MUSCALNC_LARGEDATA_DIR
	if [ ! -d "${prefix}/data/muscalnc" ]; then \
		$(MKDIR_P) ${prefix}/data; \
		$(LN_S) -f $(MUSCALNC_LARGEDATA_DIR) ${prefix}/data/muscalnc; \
		echo "USING WITH_MUSCALNC_LARGEDATA_DIR in muscalnc"; \
	fi
	cp config ${prefix}/data
else
	if [ ! -d "${prefix}/data/muscalnc" ]; then \
		$(MKDIR_P) ${prefix}/data; \
		mv muscalnc ${prefix}/data; \
		$(LN_S) -f ${prefix}/data/muscalnc .; \
		echo "NOT USING WITH_MUSCALNC_LARGEDATA_DIR in muscalnc"; \
	fi
	cp config ${prefix}/data
endif

clean:
	echo "clean"
