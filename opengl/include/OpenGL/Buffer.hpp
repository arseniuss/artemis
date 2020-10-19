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

#ifndef OPENGL_BUFFER_HPP
#define OPENGL_BUFFER_HPP

#include <Graphics/Buffer.hpp>

#include <glad.h>

namespace OpenGL {

    class Buffer : public Graphics::Buffer {
    private:
        GLuint _id = (GLuint) - 1;
        GLenum bufferType;

        void create(enum Graphics::BufferType type, const float *data, size_t size);
    public:
        Buffer(enum Graphics::BufferType type, const float *data, size_t size);
        
        void Use() const override;

    };
}

#endif /* !OPENGL_BUFFER_HPP */
