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

#ifndef WORLD_COORDINATES_HPP
#define WORLD_COORDINATES_HPP

#include <unordered_map>

#include <glm/ext/vector_int3.hpp>

namespace World {

    struct ChunkMapHash {
        // http://www.beosil.com/download/CollisionDetectionHashing_VMV03.pdf

        std::size_t operator()(const glm::ivec3& position) const {
            return (position.x * 88339) ^ (position.z * 91967) ^ (position.z * 126323);
        }
    };

    template<typename T>
    using ChunkMap = std::unordered_map<glm::ivec3, T, ChunkMapHash>;

    glm::ivec3 GetChunkPosition(const glm::ivec3& blockPosition);
    glm::ivec3 GetBlockPosition(const glm::ivec3& blockPosition);

    int GetBlockIndex(const glm::ivec3& blockPosition);
    glm::ivec3 GetGlobalPosition(const glm::ivec3& blockPosition,
            const glm::ivec3& chunkPosition);
}

#endif /* !WORLD_COORDINATES_HPP */

