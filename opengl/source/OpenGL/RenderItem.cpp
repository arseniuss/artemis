/**
 *  Artemis game
 *  Copyright (C) 2021 Armands Arseniuss Skolmeisters
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this library.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <Common.hpp>
#include <Common/Debug.hpp>
#include <Common/Dictionary.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Geometry.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Materials/CustomMaterial.hpp>
#include <Graphics/Materials/PointsMaterial.hpp>
#include <Graphics/Objects/Line.hpp>
#include <Graphics/Objects/Points.hpp>
#include <Graphics/Objects/Points.hpp>
#include <Graphics/Scene.hpp>
#include <OpenGL/Binding.hpp>
#include <OpenGL/MaterialProperties.hpp>
#include <OpenGL/Program.hpp>
#include <OpenGL/RenderItem.hpp>

#include <glad.h>

using namespace OpenGL;

RenderItem::~RenderItem() {

}

void RenderItem::Reset(State& state) {
    // TODO: delete data
}

void RenderItem::Build() {


}

void RenderItem::Update(std::shared_ptr<Graphics::Object> o) {
    size_t h = o->GetHash();

    if (h == Common::__hash<Graphics::Scene>()) {

    } else if (h == Common::__hash<Graphics::Points>()) {
        auto p = std::static_pointer_cast<Graphics::Points>(o);

        //auto *g = p->GetGeometry();
        //auto *m = p->GetMaterial();
    } else {
        Common::Error() << "Incorrect hash for: " << o->GetName() << std::endl;

    }

}

bool RenderItem::needsUpdate() {
    return true;
}

/*
void RenderItem::setupBinding(State& state, std::shared_ptr<Program> program, std::shared_ptr<Graphics::Geometry> geo) {
    auto binding = state.GetBindingState(geo);
    bool updateBuffers = needsUpdate();
    auto mappings = state.GetMappings(geometry);

    binding->Use();

    if (updateBuffers) {

        auto& programAttributes = program->GetAttributes();

        for (ProgramAttributes::value_type p : programAttributes) {
            std::string name = p.first;
            ProgramAttribute programAttribute = p.second;

            if (programAttribute.location >= 0) {

                if (mappings.contains(name)) {
                    auto map = mappings[name];
                    GLenum bufferType;
                    int type = map->first->GetType();

                    switch (type) {
                        case Graphics::CONST_BUFFER:
                            bufferType = GL_STATIC_DRAW;
                            break;
                        case Graphics::DYNAMIC_BUFFER:
                            bufferType = GL_DYNAMIC_DRAW;
                            break;
                        default:
                            throw std::runtime_error("Unrecognised buffer type: " + std::to_string(type));
                            break;
                    }

                    glBindBuffer(GL_ARRAY_BUFFER, map->second);
                    glBufferData(GL_ARRAY_BUFFER, map->first->GetSize(), map->first->GetData(), bufferType);
                    // TODO: change 3
                    glVertexAttribPointer(programAttribute.location, 3, )
                }
            }
        }
    }
    


}
 */
std::shared_ptr<Program> RenderItem::setProgram(State state, Common::Dictionary& properties,
        std::shared_ptr<Graphics::Camera> camera, std::shared_ptr<Graphics::Material> mat,
        std::shared_ptr<Graphics::Object> obj) {
    MaterialProperties& materialProperties = properties.Get<MaterialProperties>(mat->GetTypeName());

    bool needsProgramChange = false;

    if (mat->GetVersion() == materialProperties.GetVersion()) {

    } else {
        needsProgramChange = true;
        materialProperties.SetVersion(mat->GetVersion());
    }

    std::shared_ptr<Program> program = materialProperties.GetProgram();
    if (needsProgramChange || !program.get()) {
        program = std::make_shared<Program>();

        program->Build(materialProperties);

        materialProperties.SetProgram(program);
    }

    bool refreshProgram = false;
    bool refreshMaterial = false;
    bool refreshLights = false;

    auto programUniforms = program->GetUniforms();

    if (state.ChangeProgram(program)) {
        refreshProgram = true;
        refreshMaterial = true;
        refreshLights = true;
    }

    if (refreshProgram || state.GetCamera() != camera) {
        programUniforms.Set("projectionMatrix", camera->GetProjectionMatrix());

        if (state.GetCamera() != camera) {
            state.SetCamera(camera);

            refreshMaterial = true;
            refreshLights = true;
        }
    }

    if (refreshMaterial) {
        auto h = obj->GetHash();

        if (h == Graphics::PointsMaterial::Hash) {
            auto pm = std::static_pointer_cast<Graphics::PointsMaterial> (mat);

            programUniforms.Set("size", pm->GetPointSize());
        }
    }

    //programUniforms.Set("modelViewMatrix", obj->modelViewMatrix);
    //programUniforms.Set("normalMatrix", camera->normalMatrix);
    //programUniforms.Set("modelMatrix", camera->matrix);

    (void) (refreshLights);

    return program;
}

void RenderItem::Render(State& state, Common::Dictionary& properties, std::shared_ptr<Graphics::Camera> camera) {
    GLenum mode = 0;
    GLint start = 0;
    GLsizei count = 0;

    if (object.expired()) {
        Common::Debug() << "Object expired" << std::endl;
        return;
    }
    if (material.expired()) {
        Common::Debug() << "Material expired" << std::endl;
        return;
    }
    if (geometry.expired()) {
        Common::Debug() << "Geometry expired" << std::endl;
        return;
    }

    auto obj = object.lock();
    auto mat = material.lock();
    auto geo = geometry.lock();


    //obj->modelViewMatrix = camera->matrixWorldInverse * obj->matrixWorld;
    //obj->normalMatrix = glm::transpose(glm::inverse(obj->modelViewMatrix));

    auto program = setProgram(state, properties, camera, mat, obj);

    state.SetMaterial(mat);
    state.GetBindingState(geo);

    // TODO
    start = 0;
    count = geo->GetSize();

    auto h = obj->GetHash();

    if (h == Graphics::Line::Hash) {
        auto o = std::static_pointer_cast<Graphics::Line> (obj);
        auto lineWidth = o->GetLineWidth();

        state.SetLineWidth(lineWidth);

        if (o->IsLineSegments()) {
            mode = GL_LINES;
        } else if (o->IsLineLoop()) {
            mode = GL_LINE_LOOP;
        } else {
            mode = GL_LINE_STRIP;
        }
    } else if (h == Graphics::Points::Hash) {
        mode = GL_POINTS;
    } else {
        mode = GL_TRIANGLES;
    }



    if (obj->IsInstancedMesh()) {
        glDrawArraysInstanced(mode, start, count, obj->count);
    } else {
        glDrawArrays(mode, start, count);
    }
}

