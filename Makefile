TARGETS = \
    common \
    enet \
    opengl \
    plugins/default \
    game

.PHONY: $(TARGETS)

all: $(TARGETS)

$(TARGETS): 
	$(MAKE) -C $@ all
	
clean:
	@ for i in $(TARGETS); do \
	    $(MAKE) -C $$i clean || exit 1; \
	done
