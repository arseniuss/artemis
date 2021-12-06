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
    class BaseBuffer;

    using BufferMap = std::map<std::string, std::shared_ptr<BaseBuffer>>;

    class BufferGeometry : public Common::Observable, public std::enable_shared_from_this<BufferGeometry> {
        size_t _size;
        BufferMap _buffers;
        bool _computed = false;
    public:
        BufferGeometry();
        virtual ~BufferGeometry();

        virtual void SetAttribute(const std::string& name, std::shared_ptr<BaseBuffer> buffer);
        virtual bool HasAttribute(const std::string& name) const;
        const std::shared_ptr<BaseBuffer> GetAttribute(const std::string& name);

        BufferMap& GetBuffers();

        void Compute();

        size_t GetSize() const;
    };
}

#endif /* !GRAPHICS_GEOMETRY_HPP */
