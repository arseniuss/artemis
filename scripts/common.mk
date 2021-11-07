
OBJECTS = $(addprefix $(OBJDIR)/,$(SOURCES:=.o))
DEPS = $(addprefix $(OBJDIR)/,$(SOURCES:=.d))

CFLAGS += -Wall
CXXFLAGS += -Wall
LDFLAGS += -lc

ifndef NDEBUG
CFLAGS += -g
CXXFLAGS += -g
LDFLAGS += -g
else
CFLAGS += -O3
CXXFLAGS += -O3
LDFLAGS += -g
endif

CFLAGS += $(foreach _lib,$(LIBS),$(shell pkg-config --cflags $(_lib)))
CXXFLAGS += $(foreach _lib,$(LIBS),$(shell pkg-config --cflags $(_lib)))
LDFLAGS += $(foreach _lib,$(LIBS),$(shell pkg-config --libs $(_lib)))

$(STATIC_LIBS): %.a: 
	$(MAKE) -C $(dir $@) all
	
$(SHARED_LIBS): %.so:
	$(MAKE) -C $(dir $@) all

$(OBJDIR)/%.c.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(OBJDIR)/%.cpp.o: %.cpp
	@ mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -c -o $@ $<

depends:
	@ for lib in $(LIBS); do \
	    pkg-config --exists $$lib || { echo Package $$lib do not exist!; exit 1; } \
	done

clean: clean-static-libs clean-shared-libs
	@ rm -frv $(BUILDDIR) $(TARGET)
	
clean-static-libs:
	@ for lib in $(foreach _lib,$(STATIC_LIBS),$(dir $(_lib))); do \
	    $(MAKE) -C $$lib clean; \
	done
	
clean-shared-libs:
	@ for lib in $(foreach _lib,$(SHARED_LIBS),$(dir $(_lib))); do \
	    $(MAKE) -C $$lib clean; \
	done

-include $(DEPS)
