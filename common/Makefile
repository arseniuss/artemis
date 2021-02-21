TARGET = libartemis_common.a

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
SOURCES = \
    source/Common/Application.cpp \
    source/Common/Config.cpp \
    source/Common/Debug.cpp \
    source/Common/PluginManager.cpp \
    source/Common/State.cpp \
    source/Galaxy/ClusterGalaxyGenerator.cpp \
    source/Galaxy/GalaxyGenerator.cpp \
    source/Galaxy/SphereGalaxyGenerator.cpp \
    source/Graphics/Buffer.cpp \
    source/Graphics/Camera.cpp \
    source/Graphics/Geometry.cpp \
    source/Graphics/Materials/PointsMaterials.cpp \
    source/Graphics/Object.cpp \
    source/Graphics/Objects/Points.cpp \
    source/Graphics/Scene.cpp \
    source/Graphics/Utils.cpp \
    source/Graphics/ViewFrustum.cpp \
    source/Maths/Frustum.cpp \
    source/Maths/Plane.cpp \
    source/Maths/Sphere.cpp \
    source/Network/Context.cpp \
    source/Network/Event.cpp \
    source/Network/Payload.cpp \
    source/Network/Peer.cpp \
    source/World/Block.cpp \
    source/World/Chunk.cpp \
    source/World/ChunkManager.cpp \
    source/World/Coordinates.cpp

CFLAGS = -Iinclude -I../include -fPIC -frtti
CXXFLAGS = -Iinclude -I../include -fPIC -std=c++2a -frtti
LDFLAGS = 

all: $(TARGET)
	
include ../scripts/common.mk
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rvs $@ $^
