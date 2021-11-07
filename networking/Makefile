TARGET = libartemis_networking.a

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

INCLUDES = \
    include \
    ../common/include
SOURCES = \
    source/Network/Context.cpp \
    source/Network/Event.cpp \
    source/Network/Payload.cpp \
    source/Network/Peer.cpp

CFLAGS = $(addprefix -I,$(INCLUDES)) -fPIC -frtti
CXXFLAGS = $(addprefix -I,$(INCLUDES)) -fPIC -std=c++2a -frtti
LDFLAGS = 

all: $(TARGET)
	
include ../scripts/common.mk
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rvs $@ $^

