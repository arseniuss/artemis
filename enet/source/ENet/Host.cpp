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

#include <enet/enet.h>

#include <ENet/Host.hpp>
#include <ENet/Event.hpp>

#include <Network/Context.hpp>

using namespace ENet;

Host::Host() {
    create(1);
}

Host::Host(int maxConnections) : Network::Host(maxConnections) {
    create(maxConnections);
}

Host::~Host() {
    if (_handle) {
        enet_host_destroy(_handle);
    }
}

void Host::create(int maxConnections) {
    ENetAddress addr;

    addr.host = ENET_HOST_ANY;
    addr.port = Network::Context::DefaultPort;

    _handle = enet_host_create(&addr, maxConnections, 2, 0, 0);
}

bool Host::PullEvent(Network::Event** event) {
    ENetEvent e;

    if (enet_host_service(_handle, &e, 0)) {
        if (e.type == ENET_EVENT_TYPE_NONE)
            return false;

        *event = new Event(e);

        return true;
    }

    return false;
}

