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
#include <Graphics/Geometries/BufferGeometry.hpp>

using namespace Graphics;

BufferGeometry::BufferGeometry() {
    _size = 0;
}

BufferGeometry::~BufferGeometry() {
    DEBUG("Geometry died.");
}

void BufferGeometry::SetAttribute(const std::string& name, std::shared_ptr<BaseBuffer> buffer) {
    buffer->SetName(name);
    _buffers.emplace(name, buffer);
}

BufferMap& BufferGeometry::GetBuffers() {
    return _buffers;
}

void BufferGeometry::Compute() {
    if (_buffers.contains("position")) {
        _size = _buffers["position"]->GetCount() / 3;
    }
    _computed = true;
}

size_t BufferGeometry::GetSize() const {
    return _size;
}


