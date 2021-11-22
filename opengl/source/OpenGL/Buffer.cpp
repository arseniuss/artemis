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
#include <OpenGL/Debug.hpp>

#include "glad.h"

using namespace OpenGL;

Buffer::Buffer(std::shared_ptr<Graphics::BaseBuffer> buffer) {
    GLenum bufferType;

    DEBUG("Creating buffer " << buffer->GetName());

    GL_CHECK2(glGenBuffers, 1, &_id);
    GL_CHECK2(glBindBuffer, GL_ARRAY_BUFFER, _id);

    int type = buffer->GetBufferType();

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

    size_t itemType = buffer->GetType();

    if (itemType == typeid (float).hash_code()) {
        _type = GL_FLOAT;
    } else {
        throw std::runtime_error("Unregonised buffer type: " + std::to_string(itemType));
    }

    GL_CHECK2(glBufferData, GL_ARRAY_BUFFER, buffer->GetDataSize(), buffer->GetData(), bufferType);
    GL_CHECK2(glBindBuffer, GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer() {
    GL_CHECK2(glDeleteBuffers, 1, &_id);
}

GLenum Buffer::GetType() const {
    return _type;
}

GLuint Buffer::GetId() const {
    return _id;
}
