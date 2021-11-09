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

#ifndef GRAPHICS_GEOMETRY_HPP
#define GRAPHICS_GEOMETRY_HPP

#include <map>
#include <memory>
#include <string>

#include <Common/Observer.hpp>

namespace Graphics {
    class Buffer;

    using BufferMap = std::map<std::string, std::shared_ptr<Buffer>>;

    class Geometry : public Common::Observable, public std::enable_shared_from_this<Geometry> {
        size_t _size;
        BufferMap _buffers;
    public:
        Geometry();
        virtual ~Geometry();

        virtual void AddBuffer(const std::string& name, std::shared_ptr<Buffer> buffer);

        BufferMap& GetBuffers();

        void Compute();

        size_t GetSize() const {
            return _size;
        }
    };
}

#endif /* !GRAPHICS_GEOMETRY_HPP */
