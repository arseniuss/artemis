/**
 *  Artemis game
 *  Copyright (C) 2020 Armands Arseniuss Skolmeisters
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

#ifndef WORLD_ENTITY_HPP
#define WORLD_ENTITY_HPP

#include <glm/ext/vector_float3.hpp>


namespace World {

    struct Entity {
        glm::vec3 position{0.0f};
        glm::vec3 rotation{0.0f};
        glm::vec3 velocity{0.0f};
    };
}

#endif /* !WORLD_ENTITY_HPP */
