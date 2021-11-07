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

#ifndef WORLD_BLOCK_HPP
#define WORLD_BLOCK_HPP

#include <string>

#include <glm/vec2.hpp>

#include <Common/Singleton.hpp>

namespace World {

    using BlockId = uint32_t;

    class Block : public Common::Singleton {
        friend class BlockManager;

    private:
        BlockId _id = -1;
    protected:
        Block() = default;
    public:

        std::string name;

        enum class MeshType {
            Cube = 0,
            Cross = 1
        };

        enum class ShaderType {
            Chunk = 0,
            Liquid = 1,
            Flora = 2
        };

        glm::ivec2 textureTopCoord;
        glm::ivec2 textureSideCoord;
        glm::ivec2 textureBottomCoord;

        MeshType meshType;
        ShaderType shaderType;

        bool isQpaque;
        bool isCollidable;

    };
}

#endif /* !WORLD_BLOCK_HPP */
