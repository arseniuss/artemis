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

#ifndef GALAXY_STAR_HPP
#define GALAXY_STAR_HPP

#include <glm/glm.hpp>

#include <string>

namespace Galaxy {

    struct Star {
        std::string name;
        glm::vec3 position;
        glm::vec3 color;

        Star(glm::vec3 p, std::string n, double t) : name(n), position(p) {
            
        }
    };
}

#endif /* !GALAXY_STAR_HPP */
