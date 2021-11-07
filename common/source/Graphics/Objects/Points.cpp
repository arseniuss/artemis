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

#include <Graphics/Geometry.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Objects/Points.hpp>

using namespace Graphics;

static unsigned int pointIndex = 0;

size_t Points::Hash = typeid (Points).hash_code();

Points::Points(std::shared_ptr<Geometry> geo, std::shared_ptr<Material> mat) : ViewObject(geo, mat) {
    _name = "Points #" + std::to_string(pointIndex++);
    _hash = typeid (Points).hash_code();
}

