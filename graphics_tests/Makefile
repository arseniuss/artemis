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
    source/03_matrices_test.cpp \
    source/04_colored_cube.cpp \
    source/05_textured_cube.cpp \
    source/06_rotate_lookat.cpp \
    source/Test.cpp \
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

.PHONY: all clean depends $(STATIC_LIBS) $(SHARED_LIBS) copy-shared-libs copy-data

all: depends $(TARGET) $(SHARED_LIBS) copy-shared-libs copy-data
	
include ../scripts/common.mk

copy-data: 
	cp -vr data $(BUILDDIR)

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

