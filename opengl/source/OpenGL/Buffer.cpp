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

#include <OpenGL/Buffer.hpp>
#include <stdexcept>

using namespace OpenGL;

Buffer::Buffer(Graphics::BufferType type, const float* data, size_t size) :
Graphics::Buffer(type, data, size) {
    create(type, data, size);
}

void Buffer::create(Graphics::BufferType type, const float* data, size_t size) {
    switch (type) {
        case Graphics::BufferType::Array:
            bufferType = GL_ARRAY_BUFFER;
            break;
        default:
            throw std::runtime_error("Unrecognised buffer type");
            break;
    }

    glGenBuffers(1, &_id);
    glBindBuffer(bufferType, _id);
    glBufferData(bufferType, size, data, GL_STATIC_DRAW);
}

void Buffer::Use() const {
    glBindBuffer(bufferType, _id);
}



