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
#include <Graphics/Geometries/BufferGeometry.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Materials/BasicMeshMaterial.hpp>
#include <Graphics/Materials/CustomMaterial.hpp>
#include <Graphics/Materials/MeshMaterial.hpp>
#include <Graphics/Materials/PointsMaterial.hpp>
#include <Graphics/Objects/Line.hpp>
#include <Graphics/Objects/Points.hpp>
#include <Graphics/Objects/Points.hpp>
#include <Graphics/Scene.hpp>
#include <OpenGL/Binding.hpp>
#include <OpenGL/Debug.hpp>
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

bool RenderItem::needsUpdate() {
    return true;
}

std::shared_ptr<Program> RenderItem::setProgram(State state, Common::Dictionary& properties,
        std::shared_ptr<Graphics::Camera> camera, std::shared_ptr<Graphics::Material> mat,
        std::shared_ptr<Graphics::Object> obj) {

    std::shared_ptr<MaterialProperties> props = MaterialProperties::GetOrEmpty(mat);
    bool needsProgramChange = false;

    if (mat->GetVersion() != props->GetVersion()) {
        needsProgramChange = true;
        props->Update(mat);
    }


    std::shared_ptr<Program> program = props->GetProgram();
    if (needsProgramChange || !program.get()) {
        program = std::make_shared<Program>();

        program->Build(props);

        props->SetProgram(program);
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
        if (programUniforms.Exists("projectionMatrix"))
            programUniforms.Set("projectionMatrix", camera->GetProjectionMatrix());

        if (state.GetCamera() != camera) {
            state.SetCamera(camera);

            refreshMaterial = true;
            refreshLights = true;
        }
    }

    if (refreshMaterial) {
        auto h = mat->GetHash();

        if (h == Graphics::PointsMaterial::Hash) {
            auto pm = std::static_pointer_cast<Graphics::PointsMaterial> (mat);

            programUniforms.Set("size", pm->GetPointSize());
        } else if (h == Graphics::MeshMaterial::Hash) {
            auto m = std::static_pointer_cast<Graphics::MeshMaterial>(mat);
            
        } else if (h == Graphics::BasicMeshMaterial::Hash) {
            auto m = std::static_pointer_cast<Graphics::BasicMeshMaterial>(mat);

            programUniforms.Set("color", m->GetColor().GetVector());
        } else {
            throw std::runtime_error("Unsupported material: " + mat->GetName());
        }

        props->SetVersion(mat->GetVersion());
    }

    if (programUniforms.Exists("viewMatrix"))
        programUniforms.Set("viewMatrix", camera->GetViewMatrix());
    //programUniforms.Set("normalMatrix", camera->normalMatrix);
    if (programUniforms.Exists("modelMatrix"))
        programUniforms.Set("modelMatrix", obj->GetMatrix());

    (void) (refreshLights);

    DEBUG_ONCE(programUniforms.Dump());

    return program;
}

void RenderItem::Render(State& state, Common::Dictionary& properties, std::shared_ptr<Graphics::Camera> camera) {
    GLenum mode = 0;
    GLint start = 0;
    GLsizei count = 0;

    if (object.expired()) {
        DEBUG("Object expired");
        return;
    }
    if (material.expired()) {
        DEBUG("Material expired");
        return;
    }
    if (geometry.expired()) {
        DEBUG("Geometry expired");
        return;
    }

    auto obj = object.lock();
    auto mat = material.lock();
    auto geo = geometry.lock();

    geo->Compute();

    //obj->modelViewMatrix = camera->matrixWorldInverse * obj->matrixWorld;
    //obj->normalMatrix = glm::transpose(glm::inverse(obj->modelViewMatrix));

    auto program = setProgram(state, properties, camera, mat, obj);

    state.SetMaterial(mat);
    auto binding = state.GetBindingState(geo, program);

    binding->Use();

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
        GL_CHECK2(glDrawArraysInstanced, mode, start, count, obj->count);
    } else {
        GL_CHECK2(glDrawArrays, mode, start, count);
    }
}

