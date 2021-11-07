TARGET = libartemis_default.so

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

INCLUDES = \
    include \
    ../../common/include \
    ../../logic/include
SOURCES = \
    source/World/GrassBlock.cpp \
    source/Plugin.cpp

CFLAGS = $(addprefix -I,$(INCLUDES)) -fPIC
CXXFLAGS = $(addprefix -I,$(INCLUDES)) -fPIC -std=c++2a
LDFLAGS = 

all: $(TARGET)
	
include ../../scripts/common.mk
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)
	objdump -D $@ > $@.dump
