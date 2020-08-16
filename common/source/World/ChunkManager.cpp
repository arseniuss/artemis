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

#include <utility>

#include <World/Coordinates.hpp>
#include <World/ChunkManager.hpp>

using namespace World;

Chunk& ChunkManager::Add(const glm::ivec3& position) {
    auto it = chunks.find(position);
    if (it == chunks.cend()) {
        return chunks.emplace(std::piecewise_construct,
                std::forward_as_tuple(position),
                std::forward_as_tuple(*this, position))
                .first->second;
    }
    return it->second;
}

const Chunk& ChunkManager::Get(const glm::ivec3& position) {
    auto it = chunks.find(position);
    if (it == chunks.cend()) {
        static Chunk errorChunk(*this,{0, 0, 0});

        return errorChunk;
    }
    return it->second;
}

BlockId ChunkManager::GetBlock(const glm::ivec3& position) {
    auto chunkPosition = GetChunkPosition(position);
    auto it = chunks.find(chunkPosition);

    if (it == chunks.cend()) {
        return 0;
    }

    return it->second.UnsafeGetBlock(GetBlockPosition(position));
}

void ChunkManager::SetBlock(const glm::ivec3& position, BlockId block) {
    auto chunkPosition = GetChunkPosition(position);
    auto it = chunks.find(chunkPosition);
    auto local = GetBlockPosition(position);

    if (it != chunks.cend()) {
        it->second.UnsafeSetBlock(local, block);
    } else {
        Add(chunkPosition).UnsafeSetBlock(local, block);
    }
}

void ChunkManager::EnsureNeighbours(const glm::ivec3& position) {
    const auto& pos = position;

    Add(pos);
    Add({pos.x + 1, pos.y, pos.z});
    Add({pos.x - 1, pos.y, pos.z});
    Add({pos.x, pos.y + 1, pos.z});
    Add({pos.x, pos.y - 1, pos.z});
    Add({pos.x, pos.y, pos.z + 1});
    Add({pos.x, pos.y, pos.z - 1});
}

bool ChunkManager::Exists(const glm::ivec3& position) {
    return chunks.find(position) != chunks.cend();
}

bool ChunkManager::HasNeighbours(const glm::ivec3& position) {
    const auto& pos = position;

    return Exists(pos) && Exists({pos.x + 1, pos.y, pos.z}) &&
    Exists({pos.x - 1, pos.y, pos.z}) && Exists({pos.x, pos.y + 1, pos.z}) &&
    Exists({pos.x, pos.y - 1, pos.z}) && Exists({pos.x, pos.y, pos.z + 1}) &&
    Exists({pos.x, pos.y, pos.z - 1});
}




