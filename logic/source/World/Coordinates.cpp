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

#include <World/Coordinates.hpp>
#include <World/Constants.hpp>

using namespace World;

glm::ivec3 GetChunkPosition(const glm::ivec3& blockPosition) {
    int x = blockPosition.x;
    int y = blockPosition.y;
    int z = blockPosition.z;

    return {
        x < 0 ? ((x - CHUNK_SIZE) / CHUNK_SIZE) : (x / CHUNK_SIZE),
        y < 0 ? ((y - CHUNK_SIZE) / CHUNK_SIZE) : (y / CHUNK_SIZE),
        z < 0 ? ((z - CHUNK_SIZE) / CHUNK_SIZE) : (z / CHUNK_SIZE)};
}

glm::ivec3 GetBlockPosition(const glm::ivec3& blockPosition) {
    return {
        (CHUNK_SIZE + (blockPosition.x % CHUNK_SIZE)) % CHUNK_SIZE,
        (CHUNK_SIZE + (blockPosition.y % CHUNK_SIZE)) % CHUNK_SIZE,
        (CHUNK_SIZE + (blockPosition.z % CHUNK_SIZE)) % CHUNK_SIZE};
}

int GetBlockIndex(const glm::ivec3& blockPosition) {
    return blockPosition.y * CHUNK_AREA + blockPosition.z * CHUNK_SIZE +
            blockPosition.x;
}

glm::ivec3 GetGlobalPosition(const glm::ivec3& blockPosition,
        const glm::ivec3& chunkPosition) {
    return {
        blockPosition.x * CHUNK_SIZE + chunkPosition.x,
        blockPosition.y * CHUNK_SIZE + chunkPosition.y,
        blockPosition.z * CHUNK_SIZE + chunkPosition.z};
}
