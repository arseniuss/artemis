TARGETS = \
    common \
    opengl \
    plugins/default \
    server \
    client

all:
	@ for i in $(TARGETS); do \
	    make -C $$i all || exit 1; \
	done
	
clean:
	@ for i in $(TARGETS); do \
	    make -C $$i clean || exit 1; \
	done
