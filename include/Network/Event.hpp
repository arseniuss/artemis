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

#ifndef NETWORK_EVENT_HPP
#define NETWORK_EVENT_HPP

#include <Network/Peer.hpp>
#include <Network/Payload.hpp>

namespace Network {

    enum EventType {
        Connect,
        Disconnect,
        Timeout,
        Data
    };

    class Event {
    protected:
        EventType _type;
    public:
        Event();
        virtual ~Event() {};
        
        EventType GetType() const;
        
        virtual Peer GetPeer() const = 0;
        virtual Payload GetPayload() const = 0;
    };
}

#endif /* !NETWORK_EVENT_HPP */
