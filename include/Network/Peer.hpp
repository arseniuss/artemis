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

#ifndef NETWORK_PEER_HPP
#define NETWORK_PEER_HPP

#include <cstdint>

#include <Network/Payload.hpp>

namespace Network {
    class Peer {
    protected:
        uint32_t _addr = 0;
        int32_t _id = -1;
    public:
        Peer() = default;
        virtual ~Peer() = default;
        
        uint32_t GetAddr() const {
            return _addr;
        }
        
        int32_t GetId() const {
            return _id;
        }
        
        virtual void Send(Payload& payload) = 0;
    };
}

#endif /* !NETWORK_PEER_HPP */
