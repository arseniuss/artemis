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
#include <Graphics/Geometry.hpp>
#include <OpenGL/Binding.hpp>
#include <OpenGL/Buffer.hpp>

#include "glad.h"

using namespace OpenGL;

Binding::Binding(std::weak_ptr<Graphics::Geometry> geometry) {
    glGenVertexArrays(1, &_id);

    createMapping(geometry);
}

void Binding::createMapping(std::weak_ptr<Graphics::Geometry> geometry) {
    if (auto geo = geometry.lock()) {
        auto& buffers = geo->GetBuffers();

        for (Graphics::BufferMap::value_type value : buffers) {
            auto bufferName = value.first;
            auto buffer = value.second;

            std::shared_ptr<Buffer> glslBuffer = GetBuffer(value.second);
        }
    }
}

Binding::~Binding() {
    glDeleteVertexArrays(1, &_id);
}

void Binding::Use() {
    glBindVertexArray(_id);
}

std::shared_ptr<Buffer> Binding::GetBuffer(std::shared_ptr<Graphics::Buffer> buffer) {
    auto weak_buf = buffer->weak_from_this();

    if (_buffers.contains(weak_buf)) {
        return _buffers[weak_buf];
    }

    auto entry = std::make_shared<Buffer>(buffer);

    _buffers.emplace(weak_buf, entry);

    RegisterOnDestruct<Binding, Graphics::Buffer>(this, buffer,
            [](auto a, auto b) {
                a->RemoveBuffer(b); });

    return entry;
}

void Binding::RemoveBuffer(std::weak_ptr<Graphics::Buffer> buffer) {
    if (_buffers.contains(buffer)) {
        _buffers.erase(buffer);
    }
}


