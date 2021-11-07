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

#ifndef WORLD_CHUNK_HPP
#define WORLD_CHUNK_HPP

#include <array>

#include <glm/vec3.hpp>

#include <World/Block.hpp>
#include <World/Constants.hpp>

namespace World {

    class ChunkManager;

    class Chunk {
    public:
        Chunk(ChunkManager& manager, const glm::ivec3& position);

        BlockId UnsafeGetBlock(const glm::ivec3& blockPosition);
        void UnsafeSetBlock(const glm::ivec3& blockPosition, BlockId block);
        
        BlockId GetBlock(const glm::ivec3& blockPosition);
        void SetBlock(const glm::ivec3& blockPosition, BlockId block);
        
        const glm::ivec3& GetPosition() const;
    private:
        ChunkManager& manager;
        
        glm::ivec3 position;
        std::array<BlockId, CHUNK_VOLUME> blocks;
    };
}


#endif /* !WORLD_CHUNK_HPP */

