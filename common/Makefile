TARGET = libartemis_common.a

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
SOURCES = \
    source/Common/Application.cpp \
    source/Common/Config.cpp \
    source/Common/Dictionary.cpp \
    source/Common/PluginManager.cpp \
    source/Common/State.cpp \
    source/Maths/Plane.cpp \
    source/Maths/Sphere.cpp \
    source/Utility/Filesystem.cpp \
    source/Utility/Random.cpp \
    source/Utility/String.cpp

CFLAGS = -Iinclude -I../include -fPIC -frtti
CXXFLAGS = -Iinclude -I../include -fPIC -std=c++2a -frtti
LDFLAGS = 

all: $(TARGET)
	
include ../scripts/common.mk
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rvs $@ $^
