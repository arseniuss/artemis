/**
 *  Artemis game
 *  Copyright (C) 2020 Armands Arseniuss Skolmeisters
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

#include <Graphics/Buffer.hpp>
#include <OpenGL/Buffer.hpp>

#include "glad.h"

using namespace OpenGL;

Buffer::Buffer(std::shared_ptr<Graphics::Buffer> buffer) {
    GLenum bufferType;

    DEBUG("Creating buffer " << buffer->GetName());

    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);

    int type = buffer->GetType();

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

    glBufferData(GL_ARRAY_BUFFER, buffer->GetSize(), buffer->GetData(), bufferType);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &_id);
}

