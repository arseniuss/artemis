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

#include <Graphics/Objects/Mesh.hpp>

using namespace Graphics;

static unsigned int meshIndex = 0;

size_t Mesh::Hash = typeid (Mesh).hash_code();

Mesh::Mesh(std::shared_ptr<BufferGeometry> geo, std::shared_ptr<Material> mat) : ViewObject(geo, mat) {
    _name = "Mesh #" + std::to_string(meshIndex++);
    _hash = Mesh::Hash;
}

Mesh::~Mesh() {

}

