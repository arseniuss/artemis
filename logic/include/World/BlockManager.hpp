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

#ifndef WORLD_BLOCKMANAGER_HPP
#define WORLD_BLOCKMANAGER_HPP

#include <map>

#include <World/Block.hpp>
#include <Common/Singleton.hpp>

namespace World {

    class BlockManager : public Common::Singleton {
    public:
        static BlockManager& GetInstance();

        template<class BlockClass>
        void Register() {
            BlockClass* block = new BlockClass();

            block->_id = _database.size();

            _database.insert(std::pair(block->_id, block));
        }
    private:
        std::map<BlockId, Block*> _database;
    };
}

#endif /* !WORLD_BLOCKMANAGER_HPP */
