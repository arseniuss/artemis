TARGET = libartemis_enet.so

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

INCLUDES = \
    include \
    ../common/include \
    ../networking/include
SOURCES = \
    source/ENet/Client.cpp \
    source/ENet/Context.cpp \
    source/ENet/Event.cpp \
    source/ENet/Host.cpp \
    source/ENet/Peer.cpp \
    source/Plugin.cpp

CFLAGS = $(addprefix -I,$(INCLUDES))  -fPIC
CXXFLAGS = $(addprefix -I,$(INCLUDES))  -fPIC
LDFLAGS = 

LIBS = libenet

all: $(TARGET)
	
include ../scripts/common.mk

$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)
	objdump -D $@ > $(OBJDIR)/$@.dump

