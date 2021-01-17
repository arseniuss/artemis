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

#ifndef MATHS_PLANE_HPP
#define MATHS_PLANE_HPP

#include <glm/glm.hpp>

#include <Maths/Sphere.hpp>

namespace Maths {

    class Plane {
    protected:
        glm::vec3 _normal;
        float _constant;
    public:
        Plane();
        
        Plane(const glm::vec3& normal, float constant);

        Plane& Set(float x, float y, float z, float w);

        Plane& Normalize();

        Plane& Negate();

        float Distance(const glm::vec3& point) const;

        float Distance(const Sphere& sphere) const;
    };
}

#endif /* !MATHS_PLANE_HPP */
