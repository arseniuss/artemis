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

#ifndef GRAPHICS_MATHS_HPP
#define GRAPHICS_MATHS_HPP

#include <glm/gtc/quaternion.hpp>


namespace Graphics {
    namespace Maths {

        inline glm::mat4 ExtractRotation(const glm::mat4& m) {
            glm::vec3 scale;

            for (int i = 0; i < 3; i++)
                scale[i] = glm::length(glm::vec3(m[i]));

            const glm::mat3 rot(
                    glm::vec3(m[0]) / scale[0],
                    glm::vec3(m[1]) / scale[1],
                    glm::vec3(m[2]) / scale[2]
                    );

            return rot;
        }
    }
}

#endif /* !GRAPHICS_MATHS_HPP */
