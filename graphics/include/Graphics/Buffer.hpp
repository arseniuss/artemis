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

#ifndef GRAPHICS_BUFFER_HPP
#define GRAPHICS_BUFFER_HPP

#include <string>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <Common/Observer.hpp>

namespace Graphics {

    enum {
        CONST_BUFFER,
        DYNAMIC_BUFFER
    };

    class BaseBuffer : public std::enable_shared_from_this<BaseBuffer>, public Common::Observable {
    protected:

        const void* _data;
        size_t _dataSize;
        size_t _dataElementSize;


        size_t _itemSize;
        size_t _type;
        int _bufferType;
        std::string _name;
        ssize_t _stride;
        size_t _offset;
    public:
        BaseBuffer();

        size_t GetDataSize() const;
        size_t GetItemSize() const;
        size_t GetCount() const;

        const void* GetData();

        int GetBufferType() const;
        size_t GetType() const;
        ssize_t GetStride() const;
        size_t GetOffset() const;

        const std::string& GetName() const;

        void SetName(const std::string& name);
    };

    template<typename TItem>
    class Buffer : public BaseBuffer {
    public:

        Buffer(const std::vector<TItem>& data, int itemSize) : BaseBuffer() {
            _data = (const void *) data.data();
            _dataSize = data.size() * sizeof (TItem);
            _dataElementSize = sizeof (TItem);

            _itemSize = itemSize;
            _type = typeid (TItem).hash_code();
            _bufferType = CONST_BUFFER;
        }

        Buffer(const TItem* data, size_t dataSize, int itemSize) : BaseBuffer() {
            _data = data;
            _dataSize = dataSize;
            _dataElementSize = sizeof (TItem);

            _itemSize = itemSize;
            _type = typeid (TItem).hash_code();
            _bufferType = CONST_BUFFER;
        }
    };
}

#endif /* !GRAPHICS_BUFFER_HPP */
