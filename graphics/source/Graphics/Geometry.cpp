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
#include <Graphics/Geometry.hpp>

using namespace Graphics;

Geometry::Geometry() {
    _size = 0;
}

Geometry::~Geometry() {
    Common::Debug() << "Geometry died." << std::endl;
}

void Geometry::AddBuffer(const std::string& name, std::shared_ptr<Buffer> buffer) {
    buffer->SetName(name);
    _buffers.emplace(name, buffer);
}

BufferMap& Geometry::GetBuffers() {
    return _buffers;
}

void Geometry::Compute() {
    if (_buffers.contains("position")) {
        _size = _buffers["position"]->GetSize() / 3;
    }
}

