TARGET = libartemis_common.a

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
SOURCES = \
    source/Common/Application.cpp \
    source/Common/Debug.cpp \
    source/Common/PluginManager.cpp \
    source/Common/State.cpp \
    source/Gui/Oui.cpp \
    source/World/Block.cpp \
    source/World/Chunk.cpp \
    source/World/ChunkManager.cpp \
    source/World/Coordinates.cpp \
    source/oui.cpp

CFLAGS = -Iinclude -I../include -fPIC
CXXFLAGS = -Iinclude -I../include -fPIC -std=c++2a
LDFLAGS = 

all: $(TARGET)
	
include ../scripts/common.mk
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rvs $@ $^
	objdump -D $@ > $(BUILDDIR)/$@.dump
