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

#include <Graphics/Buffer.hpp>

using namespace Graphics;

BaseBuffer::BaseBuffer() {
    _data = nullptr;
    _dataSize = 0;
    _dataElementSize = 0;
    
    _type = CONST_BUFFER;
    _data = nullptr;
    _dataSize = 0;
    _itemSize = 0;
    _offset = 0;
    _stride = 0;
}

size_t BaseBuffer::GetDataSize() const {
    return _dataSize;
}

size_t BaseBuffer::GetItemSize() const {
    return _itemSize;
}

size_t BaseBuffer::GetCount() const {
    return _dataSize / _dataElementSize;
}

const void* BaseBuffer::GetData() {
    return _data;
}

int BaseBuffer::GetBufferType() const {
    return _bufferType;
}

size_t BaseBuffer::GetType() const {
    return _type;
}

ssize_t BaseBuffer::GetStride() const {
    return _stride;
}

size_t BaseBuffer::GetOffset() const {
    return _offset;
}

const std::string& BaseBuffer::GetName() const {
    return _name;
}

void BaseBuffer::SetName(const std::string& name) {
    _name = name;
}

