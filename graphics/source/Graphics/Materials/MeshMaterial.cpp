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

#include <Graphics/Materials/MeshMaterial.hpp>

using namespace Graphics;

int meshMaterialCounter = 0;

size_t MeshMaterial::Hash = typeid (MeshMaterial).hash_code();

MeshMaterial::MeshMaterial() : Material() {
    _hash = MeshMaterial::Hash;
    _name = "mesh material #" + std::to_string(++meshMaterialCounter);
    _typeName = "mesh material";

    _hasTexture = false;
}

bool MeshMaterial::HasTexture() const {
    return _hasTexture;
}

void MeshMaterial::SetTexture(std::shared_ptr<Texture> texture) {
    _texture = texture;
    _hasTexture = texture.get() ? true : false;
}

std::shared_ptr<Texture> MeshMaterial::GetTexture() {
    return _texture;
}
