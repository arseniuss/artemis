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

Material::Material() : _typeName(unnamed) {
    _id = ++materialCounter;
    _name = "unnamed material #" + std::to_string(_id);
    _version = 1;

    _isVisible = true;

    _transparent = false;
}

Material::Material(const std::string& name, const std::string& typeName) : Material() {
    _name = name;
    _typeName = typeName;
}

const std::string& Material::GetName() const {
    return _name;
}

bool Material::IsTransparent() const {
    return _transparent;
}

bool Material::IsVisible() const {
    return _isVisible;
}
