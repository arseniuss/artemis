TARGET = libartemis_enet.so

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

SOURCES = \
    source/ENet/Client.cpp \
    source/ENet/Context.cpp \
    source/ENet/Event.cpp \
    source/ENet/Host.cpp \
    source/ENet/Peer.cpp \
    source/Plugin.cpp

CFLAGS = -I include -I../include  -fPIC
CXXFLAGS = -Iinclude -I../include  -fPIC
LDFLAGS = 

LIBS = libenet

all: $(TARGET)
	
include ../scripts/common.mk

$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)
	objdump -D $@ > $(OBJDIR)/$@.dump

