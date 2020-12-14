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

#include <stdexcept>

#include <enet/enet.h>

#include <ENet/Client.hpp>

using namespace ENet;

Client::Client() : Network::Client() {
    _handle = enet_host_create(nullptr, 1, 2, 0, 0);
}

void Client::Connect(const std::string& address, uint16_t port) {
    ENetAddress addr{};

    addr.port = port;

    if (enet_address_set_host(&addr, address.c_str())) {
        throw std::runtime_error("Cannot set address");
    }

    ENetPeer *peer = enet_host_connect(_handle, &addr, 2, 0);
    if (peer == nullptr) {
        throw std::runtime_error("Cannot connect");
    }
}

Network::ConnectionStatus Client::GetConnectionStatus() {
    ENetEvent event;
    int ret = enet_host_service(_handle, &event, _connectTimeout);

    if (ret < 0) {
        return Network::Failed;
    }

    if (ret > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                return Network::Connected;
            case ENET_EVENT_TYPE_DISCONNECT:
                return Network::Disconnected;
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                return Network::Received;
        }

        return Network::Failed;
    }

    return Network::Connecting;
}



