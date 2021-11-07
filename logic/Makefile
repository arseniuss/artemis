TARGET = libartemis_logic.a

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

INCLUDES = \
    include \
    ../common/include

SOURCES = \
    source/Galaxy/ClusterGalaxyGenerator.cpp \
    source/Galaxy/GalaxyGenerator.cpp \
    source/Galaxy/SphereGalaxyGenerator.cpp \
    source/World/Block.cpp \
    source/World/Chunk.cpp \
    source/World/ChunkManager.cpp \
    source/World/Coordinates.cpp

CFLAGS = $(addprefix -I,$(INCLUDES)) -fPIC -frtti
CXXFLAGS = $(addprefix -I,$(INCLUDES)) -fPIC -std=c++2a -frtti
LDFLAGS = 

all: $(TARGET)
	
include ../scripts/common.mk
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rvs $@ $^

