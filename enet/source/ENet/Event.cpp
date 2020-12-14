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

#include <ENet/Event.hpp>
#include <ENet/Peer.hpp>
#include <Network/Event.hpp>

using namespace ENet;

Event::Event(ENetEvent& e) : _e(e) {
    switch (_e.type) {
        case ENET_EVENT_TYPE_NONE:
            break;
        case ENET_EVENT_TYPE_CONNECT:
            _type = Network::Connect;
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            _type = Network::Disconnect;
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            _type = Network::Data;
            break;
    }
}

Event::~Event() {

}

std::shared_ptr<Network::Peer> Event::GetPeer() const {
    return std::shared_ptr<Network::Peer>(new ENet::Peer(_e.peer));
}

Network::Payload Event::GetPayload() const {
    return Network::Payload((char *) _e.packet->data, _e.packet->dataLength);
}



