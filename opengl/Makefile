TARGET = libartemis_opengl.so

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

SOURCES = \
    source/NanoVG/NanoVG.cpp \
    source/NanoVG/nanovg.c \
    source/OpenGL/Context.cpp \
    source/OpenGL/Gui.cpp \
    source/Plugin.cpp \
    source/glad.c

CFLAGS = -I include -I../include -I../gui/include  -fPIC
CXXFLAGS = -Iinclude -I../include -I../gui/include -fPIC
LDFLAGS = 

all: $(TARGET)
	
include ../scripts/common.mk

$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)
	objdump -D $@ > $(OBJDIR)/$@.dump

