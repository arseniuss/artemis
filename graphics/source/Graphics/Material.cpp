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

#include <Graphics/Material.hpp>

using namespace Graphics;

static int materialCounter = 0;
std::string unnamed = "unnamed material";

size_t Material::Hash = typeid (Material).hash_code();

void Material::changed() {
    if (!_changed) {
        _version++;
        _changed = true;
    }
}

Material::Material() : _typeName(unnamed) {
    _hash = Material::Hash;
    _id = ++materialCounter;
    _typeName = "unnamed material";
    _name = "unnamed material #" + std::to_string(_id);
    _version = 1;
    _sides = SINGLE_SIDED;

    _isVisible = true;

    _transparent = false;
    _changed = false;
}

Material::Material(const std::string& name, const std::string& typeName) : Material() {
    _name = name;
    _typeName = typeName;
}

const std::string& Material::GetName() const {
    return _name;
}

const std::string& Material::GetTypeName() const {
    return _typeName;
}

bool Material::IsTransparent() const {
    return _transparent;
}

int Material::GetVersion() const {
    return _version;
}

int Material::GetSides() const {
    return _sides;
}

bool Material::IsVisible() const {
    return _isVisible;
}

size_t Material::GetHash() const {
    return _hash;
}

