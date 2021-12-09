PROGRAM = artemis

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
LIBDIR = $(BUILDDIR)/lib
DATADIR = $(BUILDDIR)/data
PLUGINDIR = $(BUILDDIR)/plugins

INCLUDES = \
    ../common/include \
    ../graphics/include \
    ../logic/include \
    ../networking/include \
    include
SOURCES = \
    source/Client/Application.cpp \
    source/Client/ConnectState.cpp \
    source/Client/GalaxyState.cpp \
    source/Client/GameState.cpp \
    source/Client/MenuState.cpp \
    source/Client/SettingState.cpp \
    source/Client/State.cpp \
    source/Server/Engine.cpp \
    source/World/BlockManager.cpp \
    source/main.cpp

TARGET = $(BUILDDIR)/bin/$(PROGRAM)

PLUGINS = \
    ../plugins/default/libartemis_default.so

CFLAGS = $(addprefix -I,$(INCLUDES))
CXXFLAGS = $(addprefix -I,$(INCLUDES)) -std=c++2a
LDFLAGS = -rdynamic -lstdc++ -lstdc++fs -ldl -pthread

LIBS = sdl2 SDL2_image glm yaml-cpp
STATIC_LIBS = \
    ../common/libartemis_common.a \
    ../graphics/libartemis_graphics.a \
    ../networking/libartemis_networking.a \
    ../logic/libartemis_logic.a
    
SHARED_LIBS = \
    ../opengl/libartemis_opengl.so \
    ../enet/libartemis_enet.so

.PHONY: all clean depends $(STATIC_LIBS) $(SHARED_LIBS) copy-shared-libs \
	copy-data copy-plugins

all: depends $(TARGET) $(SHARED_LIBS) copy-data copy-plugins copy-shared-libs
	
include ../scripts/common.mk

copy-plugins: $(PLUGINS)
	@ mkdir -p $(PLUGINDIR)
	-@ for i in $(PLUGINS); do \
	    cp -v $$i $(PLUGINDIR); \
	    cp -vr $$(dirname $$i)/data $(BUILDDIR); \
	done

copy-shared-libs: $(SHARED_LIBS)
	@ mkdir -p $(LIBDIR)
	-@ for i in $(SHARED_LIBS); do \
	    cp -v $$i $(LIBDIR); \
	    cp -vr $$(dirname $$i)/data $(BUILDDIR); \
	done
	
copy-data: 
	cp -vr data $(BUILDDIR)

$(TARGET): $(OBJECTS) $(STATIC_LIBS) 
	@ mkdir -p $(dir $@)
	$(CXX) -o $@ -Wl,--whole-archive $(STATIC_LIBS) -Wl,--no-whole-archive $(OBJECTS)  $(LDFLAGS) 
	@ chmod +x $@
