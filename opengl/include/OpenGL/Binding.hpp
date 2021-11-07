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

namespace Graphics {
    class Buffer;
    class Geometry;
}

namespace OpenGL {
    class Buffer;

    using BufferMap = std::map<std::weak_ptr<Graphics::Buffer>,
            std::shared_ptr<Buffer>, std::owner_less<>>;

    class Binding : public std::enable_shared_from_this<Binding> {
    private:
        unsigned int _id;

        BufferMap _buffers;

        void createMapping(std::weak_ptr<Graphics::Geometry> geometry);
    public:
        Binding(std::weak_ptr<Graphics::Geometry> geometry);
        ~Binding();

        void Use();

        std::shared_ptr<Buffer> GetBuffer(std::shared_ptr<Graphics::Buffer> buf);
        void RemoveBuffer(std::weak_ptr<Graphics::Buffer> buffer);
    };
}

#endif /* !OPENGL_BINDING_HPP */
