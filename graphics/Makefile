TARGET = libartemis_graphics.a

BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

INCLUDES = \
    include \
    ../include \
    ../common/include

SOURCES = \
    source/Graphics/Buffer.cpp \
    source/Graphics/Camera.cpp \
    source/Graphics/Cameras/PerspectiveCamera.cpp \
    source/Graphics/Color.cpp \
    source/Graphics/Common.cpp \
    source/Graphics/Context.cpp \
    source/Graphics/CubeTexture.cpp \
    source/Graphics/Geometries/BufferGeometry.cpp \
    source/Graphics/Material.cpp \
    source/Graphics/Materials/BasicMeshMaterial.cpp \
    source/Graphics/Materials/CustomMaterial.cpp \
    source/Graphics/Materials/MeshMaterial.cpp \
    source/Graphics/Materials/PointsMaterial.cpp \
    source/Graphics/Object.cpp \
    source/Graphics/Objects/LOD.cpp \
    source/Graphics/Objects/Light.cpp \
    source/Graphics/Objects/Line.cpp \
    source/Graphics/Objects/Mesh.cpp \
    source/Graphics/Objects/Points.cpp \
    source/Graphics/Property.cpp \
    source/Graphics/Scene.cpp \
    source/Graphics/Texture.cpp \
    source/Graphics/Utils.cpp \
    source/Graphics/ViewFrustum.cpp \
    source/Graphics/ViewObject.cpp \
    source/Maths/Frustum.cpp \
    source/Ui/FreeMovementHandler.cpp

CFLAGS = $(addprefix -I,$(INCLUDES)) -fPIC -frtti
CXXFLAGS = $(addprefix -I,$(INCLUDES)) -fPIC -std=c++2a -frtti
LDFLAGS = 

all: $(TARGET)
	
include ../scripts/common.mk
	
$(TARGET): $(OBJECTS)
	@ mkdir -p $(dir $@)
	ar rvs $@ $^
