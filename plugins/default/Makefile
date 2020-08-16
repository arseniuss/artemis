TARGET = libartemis_default.so

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
SOURCES = \
    source/World/GrassBlock.cpp \
    source/Plugin.cpp

CFLAGS = -Iinclude -I../../include -fPIC
CXXFLAGS = -Iinclude -I../../include -fPIC -std=c++2a
LDFLAGS = 

all: $(TARGET)
	
include ../../scripts/common.mk
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)
	objdump -D $@ > $@.dump
