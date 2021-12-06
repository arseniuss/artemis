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

#include <Common/Observer.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/Geometries/BufferGeometry.hpp>
#include <OpenGL/Binding.hpp>
#include <OpenGL/Buffer.hpp>
#include <OpenGL/Debug.hpp>

#include "glad.h"
#include "OpenGL/Program.hpp"

using namespace OpenGL;

Binding::Binding(std::weak_ptr<Graphics::BufferGeometry> geometry, std::shared_ptr<Program> program) : _geometry(geometry) {
    GL_CHECK2(glGenVertexArrays, 1, &_id);

    GL_CHECK2(glBindVertexArray, _id);
    createMapping(program);
    //GL_CHECK2(glBindVertexArray, 0);
}

void Binding::createMapping(std::shared_ptr<Program> program) {
    if (auto geo = _geometry.lock()) {
        auto& buffers = geo->GetBuffers();
        const ProgramAttributes& attributes = program->GetAttributes();

        for (Graphics::BufferMap::value_type value : buffers) {
            auto bufferName = value.first;
            auto buffer = value.second;

            std::shared_ptr<Buffer> glslBuffer = GetBuffer(value.second);

            auto attrIt = attributes.find(bufferName);
            if (attrIt == attributes.cend()) {
                throw std::runtime_error("Attribute not found: " + bufferName);
            }

            GL_CHECK2(glEnableVertexAttribArray, attrIt->second.location);
            GL_CHECK2(glBindBuffer, GL_ARRAY_BUFFER, glslBuffer->GetId());
            GL_CHECK2(glVertexAttribPointer,
                    attrIt->second.location,
                    buffer->GetItemSize(),
                    glslBuffer->GetType(),
                    false, // TODO
                    buffer->GetStride(),
                    (const void *) buffer->GetOffset()
                    );
            GL_CHECK2(glDisableVertexAttribArray, _id);
        }
    }
}

Binding::~Binding() {
    DEBUG("Binding " << _id << " died");

    GL_CHECK2(glDeleteVertexArrays, 1, &_id);
}

void Binding::Use() {
    GL_CHECK2(glBindVertexArray, _id);
}

std::shared_ptr<Buffer> Binding::GetBuffer(std::shared_ptr<Graphics::BaseBuffer> buffer) {
    auto weak_buf = buffer->weak_from_this();

    if (_buffers.contains(weak_buf)) {
        return _buffers[weak_buf];
    }

    auto entry = std::make_shared<Buffer>(buffer);

    _buffers.emplace(weak_buf, entry);

    RegisterOnDestruct<Binding, Graphics::BaseBuffer>(this, buffer,
            [](auto a, auto b) {
                a->RemoveBuffer(b); });

    return entry;
}

void Binding::RemoveBuffer(std::weak_ptr<Graphics::BaseBuffer> buffer) {
    DEBUG("Removing buffer");
    if (_buffers.contains(buffer)) {
        _buffers.erase(buffer);
    }
}


