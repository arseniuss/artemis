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

#include <World/Chunk.hpp>
#include <World/ChunkManager.hpp>
#include <World/Constants.hpp>
#include <World/Coordinates.hpp>

using namespace World;

static bool OutOfBounds(const glm::ivec3& pos) {
    return
    pos.x < 0 || pos.x >= CHUNK_SIZE ||
            pos.y < 0 || pos.y >= CHUNK_SIZE ||
            pos.z < 0 || pos.z >= CHUNK_SIZE;
}

Chunk::Chunk(ChunkManager& manager, const glm::ivec3& position) :
manager(manager), position(position) {

}

BlockId Chunk::UnsafeGetBlock(const glm::ivec3& blockPosition) {
    assert(!OutOfBounds(blockPosition));

    return blocks[GetBlockIndex(blockPosition)];
}

void Chunk::UnsafeSetBlock(const glm::ivec3& blockPosition, BlockId block) {
    assert(!OutOfBounds(blockPosition));

    blocks[GetBlockIndex(blockPosition)] = block;
}

BlockId Chunk::GetBlock(const glm::ivec3& blockPosition) {
    if (OutOfBounds(blockPosition)) {
        return manager.GetBlock(GetGlobalPosition(blockPosition, position));
    }
    return UnsafeGetBlock(blockPosition);
}

void Chunk::SetBlock(const glm::ivec3& blockPosition, BlockId block) {
    if (OutOfBounds(blockPosition)) {
        return manager.SetBlock(GetGlobalPosition(blockPosition, position),
                block);
    }

    UnsafeSetBlock(blockPosition, block);
}

const glm::ivec3& Chunk::GetPosition() const {
    return position;
}
