PROGRAM = graphics_tests

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
LIBDIR = $(BUILDDIR)/lib
DATADIR = $(BUILDDIR)/data
PLUGINDIR = $(BUILDDIR)/plugins

INCLUDES = \
    include \
    ../include \
    ../graphics/include \
    ../common/include
SOURCES = \
    source/main.cpp

TARGET = $(BUILDDIR)/bin/$(PROGRAM)

CFLAGS = $(addprefix -I,$(INCLUDES))
CXXFLAGS = $(addprefix -I,$(INCLUDES)) -std=c++2a
LDFLAGS = -rdynamic -lstdc++ -lstdc++fs -ldl -pthread

LIBS = sdl2 SDL2_image glm yaml-cpp
STATIC_LIBS = \
    ../common/libartemis_common.a \
    ../graphics/libartemis_graphics.a
    
SHARED_LIBS = \
    ../opengl/libartemis_opengl.so

.PHONY: all clean depends $(STATIC_LIBS) $(SHARED_LIBS) copy-shared-libs

all: depends $(TARGET) $(SHARED_LIBS) copy-shared-libs
	
include ../scripts/common.mk

copy-shared-libs: $(SHARED_LIBS)
	@ mkdir -p $(LIBDIR)
	-@ for i in $(SHARED_LIBS); do \
	    cp -v $$i $(LIBDIR); \
	    cp -vr $$(dirname $$i)/data $(BUILDDIR); \
	done

$(TARGET): $(OBJECTS) $(STATIC_LIBS) 
	@ mkdir -p $(dir $@)
	$(CXX) -o $@ -Wl,--whole-archive $(STATIC_LIBS) -Wl,--no-whole-archive $(OBJECTS)  $(LDFLAGS) 
	@ chmod +x $@

