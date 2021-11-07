TARGET = libartemis_opengl.so

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
INCLUDES = \
    include \
    ../include \
    ../common/include \
    ../graphics/include
SOURCES = \
    source/Blendish/blendish.cpp \
    source/NanoVG/NanoVG.cpp \
    source/NanoVG/nanovg.c \
    source/OpenGL/Background.cpp \
    source/OpenGL/Binding.cpp \
    source/OpenGL/Buffer.cpp \
    source/OpenGL/Capabilities.cpp \
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
    source/OpenGL/MaterialProperties.cpp \
    source/OpenGL/Program.cpp \
    source/OpenGL/RenderItem.cpp \
    source/OpenGL/Renderer.cpp \
    source/OpenGL/State.cpp \
    source/OpenGL/Uniforms.cpp \
    source/Plugin.cpp \
    source/glad.c \
    source/oui.cpp

CFLAGS = $(addprefix -I,$(INCLUDES))  -fPIC
CXXFLAGS = $(addprefix -I,$(INCLUDES)) -fPIC -std=c++2a
LDFLAGS = 

all: $(TARGET)
	
include ../scripts/common.mk

$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)
	objdump -D $@ > $(OBJDIR)/$@.dump

