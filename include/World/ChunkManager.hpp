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

#ifndef WORLD_CHUNKMANAGER_HPP
#define WORLD_CHUNKMANAGER_HPP

#include <World/Coordinates.hpp>
#include <World/Chunk.hpp>
#include <World/Block.hpp>

namespace World {

    class ChunkManager {
    public:
        Chunk& Add(const glm::ivec3& position);
        const Chunk& Get(const glm::ivec3& position);

        BlockId GetBlock(const glm::ivec3& position);
        void SetBlock(const glm::ivec3& position, BlockId block);

        void EnsureNeighbours(const glm::ivec3& position);
        bool Exists(const glm::ivec3& position);
        bool HasNeighbours(const glm::ivec3& position);
        
        const ChunkMap<Chunk>& GetMap() const;
    private:
        ChunkMap<Chunk> chunks;
    };
}

#endif /* !WORLD_CHUNKMANAGER_HPP */

