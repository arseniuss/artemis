TARGET = libartemis_opengl.so

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

SOURCES = \
    source/Blendish/blendish.cpp \
    source/NanoVG/NanoVG.cpp \
    source/NanoVG/nanovg.c \
    source/OpenGL/Context.cpp \
    source/OpenGL/Gui.cpp \
    source/OpenGL/Gui/Button.cpp \
    source/OpenGL/Gui/CheckBox.cpp \
    source/OpenGL/Gui/Label.cpp \
    source/OpenGL/Gui/LayoutBuilder.cpp \
    source/OpenGL/Gui/NumberField.cpp \
    source/OpenGL/Gui/Panel.cpp \
    source/OpenGL/Gui/RadioButton.cpp \
    source/OpenGL/Gui/TextInput.cpp \
    source/OpenGL/Gui/Widget.cpp \
    source/OpenGL/Gui/Window.cpp \
    source/OpenGL/Renderer.cpp \
    source/OpenGL/Shader.cpp \
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

