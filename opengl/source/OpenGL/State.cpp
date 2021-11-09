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

#include <memory>

#include <Graphics/Buffer.hpp>
#include <Graphics/Geometry.hpp>
#include <Graphics/Material.hpp>
#include <OpenGL/Binding.hpp>
#include <OpenGL/Program.hpp>
#include <OpenGL/State.hpp>

#include <glad.h>

using namespace OpenGL;

State::State() {

}

bool State::ChangeProgram(std::shared_ptr<Program> program) {
    if (_lastProgram != program) {
        program->Use();
        _lastProgram = program;
        return true;
    }

    return false;
}

void State::SetMaterial(std::shared_ptr<Graphics::Material> material) {
    if (material->GetSides() == Graphics::DOUBLE_SIDED) {
        glDisable(GL_CULL_FACE);
    } else {
        glEnable(GL_CULL_FACE);
    }

    // TODO
}

std::shared_ptr<Binding> State::GetBindingState(std::shared_ptr<Graphics::Geometry> geometry) {
    auto weak_geo = geometry->weak_from_this();

    if (_bindings.contains(weak_geo)) {
        return _bindings[weak_geo];
    }

    std::shared_ptr<Binding> binding = std::make_shared<Binding>(weak_geo);

    _bindings.emplace(geometry, binding);
    Common::RegisterOnDestruct<State, Graphics::Geometry>(this, geometry, [](auto a, auto b) {
        a->Remove(b);
    });

    return binding;
}

void State::Remove(std::weak_ptr<Graphics::Geometry> geometry) {
    Common::Debug() << "Removing geometry" << std::endl;
    if (_bindings.contains(geometry)) {
        _bindings.erase(geometry);
    }
}


// TODO: remove this
/*
MappingMap State::GetMappings(std::weak_ptr<Graphics::Geometry> geometry) {
    MappingMap mapping;

    if (auto geo = geometry.lock()) {
        auto& buffers = geo->GetBuffers();

        for (Graphics::BufferMap::value_type value : buffers) {
            std::shared_ptr<Graphics::Buffer> buffer = value.second;
            int id = GetBuffer(value.second);

            if (id < 0) {
                GLenum bufferType;

                switch (buffer->GetType()) {
                    case Graphics::CONST_BUFFER:
                        bufferType = GL_STATIC_DRAW;
                        break;
                    case Graphics::DYNAMIC_BUFFER:
                        bufferType = GL_DYNAMIC_DRAW;
                        break;
                    default:
                        throw std::runtime_error("Unrecognised buffer type!");
                        break;
                }

                glGenBuffers(1, (GLuint *) & id);
                //glBindBuffer(GL_ARRAY_BUFFER, id);
                //glBufferData(GL_ARRAY_BUFFER, buffer->GetSize(), buffer->GetData(), bufferType);
            }

            mapping.emplace(value.first, std::pair{value.second, id});
        }
    }

    return mapping;
}
 */

