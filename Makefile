TARGETS = \
    common \
    enet \
    game \
    graphics \
    graphics_tests \
    logic \
    networking \
    opengl \
    physics \
    plugins/default

.PHONY: $(TARGETS)

all: $(TARGETS)

$(TARGETS): 
	-$(MAKE) -C $@ all
	
clean:
	@ for i in $(TARGETS); do \
	    $(MAKE) -C $$i clean || exit 1; \
	done
