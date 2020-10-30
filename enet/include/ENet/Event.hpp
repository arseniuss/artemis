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

#ifndef ENET_EVENT_HPP
#define ENET_EVENT_HPP

#include <enet/enet.h>

#include <Network/Event.hpp>

namespace ENet {

    class Event : public Network::Event {
        ENetEvent& _e;
    public:
        Event(ENetEvent& e);
        virtual ~Event();

        Network::Peer GetPeer() const override;
        Network::Payload GetPayload() const override;
    };
}

#endif /* !ENET_EVENT_HPP */
