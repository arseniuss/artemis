TARGET = libartemis_opengl.so

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

SOURCES = \
    source/Blendish/blendish.cpp \
    source/NanoVG/NanoVG.cpp \
    source/NanoVG/nanovg.c \
    source/OpenGL/Gui/Button.cpp \
    source/OpenGL/Gui/LayoutBuilder.cpp \
    source/OpenGL/Gui/Panel.cpp \
    source/OpenGL/Gui/Widget.cpp \
    source/OpenGL/Gui/Window.cpp \
    source/OpenGL/Context.cpp \
    source/OpenGL/Gui.cpp \
    source/Plugin.cpp \
    source/glad.c \
    source/oui.cpp

CFLAGS = -I include -I../include -I../gui/include  -fPIC
CXXFLAGS = -Iinclude -I../include -I../gui/include -fPIC
LDFLAGS = 

all: $(TARGET)
	
include ../scripts/common.mk

$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)
	objdump -D $@ > $(OBJDIR)/$@.dump

