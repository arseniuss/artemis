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

#ifndef OPENGL_DEBUG_HPP
#define OPENGL_DEBUG_HPP

#include <stdexcept>

#include <glad.h>

namespace OpenGL {

    static inline void CheckOpenGLErrors() {
        GLenum err = glGetError();

        if (err != GL_NO_ERROR) {
            switch (err) {
                case GL_INVALID_ENUM:
                    throw std::runtime_error("GL invalid enum");
                case GL_INVALID_VALUE:
                    throw std::runtime_error("GL invalid value");
                case GL_INVALID_OPERATION:
                    throw std::runtime_error("GL invalid operation");
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    throw std::runtime_error("GL invalid framebuffer operator");
                case GL_OUT_OF_MEMORY:
                    throw std::runtime_error("GL out of memory");
                default:
                    throw std::runtime_error("GL unknown error");
            }
        }
    }
}

#endif /* !OPENGL_DEBUG_HPP */
