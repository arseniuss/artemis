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

#ifndef OPENGL_BINDING_HPP
#define OPENGL_BINDING_HPP

#include <map>
#include <memory>

#include <Common/Observer.hpp>

#include "glad.h"

namespace Graphics {
    class BaseBuffer;
    class Geometry;
}

namespace OpenGL {
    class Buffer;
    class Program;

    using BufferMap = std::map<std::weak_ptr<Graphics::BaseBuffer>,
            std::shared_ptr<Buffer>, std::owner_less<>>;

    class Binding : public std::enable_shared_from_this<Binding> {
    private:
        GLuint _id = 0;

        std::weak_ptr<Graphics::Geometry> _geometry;
        BufferMap _buffers;

        void createMapping(std::shared_ptr<Program> program);
    public:
        Binding(std::weak_ptr<Graphics::Geometry> geometry, std::shared_ptr<Program> program);
        virtual ~Binding();

        void Use();

        std::shared_ptr<Buffer> GetBuffer(std::shared_ptr<Graphics::BaseBuffer> buf);
        void RemoveBuffer(std::weak_ptr<Graphics::BaseBuffer> buffer);
    };
}

#endif /* !OPENGL_BINDING_HPP */
