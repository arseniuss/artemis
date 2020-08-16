PROGRAM = artemis_server

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

SOURCES = \
    source/main.cpp

TARGET = $(BUILDDIR)/bin/$(PROGRAM) 

CFLAGS = -Iinclude -I../include
CXXFLAGS = -Iinclude -I../include -std=c++2a
LDFLAGS = 

.PHONY: all clean depends $(STATIC_LIBS) $(SHARED_LIBS) copy-shared-libs \
	copy-data

all: depends $(TARGET) $(SHARED_LIBS)
	
include ../scripts/common.mk

$(TARGET): $(STATIC_LIBS) $(OBJECTS)
	@ mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(LDFLAGS) 
	@ chmod +x $@
