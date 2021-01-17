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

#include <Maths/Plane.hpp>

using namespace Maths;

Plane::Plane() {

}

Plane::Plane(const glm::vec3& normal, float constant) {
    _normal = normal;
    _constant = constant;
}

Plane& Plane::Set(float x, float y, float z, float w) {
    _normal = {x, y, z};
    _constant = w;

    return *this;
}

Plane& Plane::Normalize() {
    auto length = glm::length(_normal);

    _normal /= length;
    _constant /= length;

    return *this;
}

Plane& Plane::Negate() {
    _constant *= -1;
    _normal.x *= -1;
    _normal.y *= -1;
    _normal.z *= -1;

    return *this;
}

float Plane::Distance(const glm::vec3& point) const {
    return glm::dot(point, _normal) + _constant;
}

float Plane::Distance(const Sphere& sphere) const {
    return Distance(sphere.GetCenter()) - sphere.GetRadius();
}
