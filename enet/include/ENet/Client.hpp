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

#ifndef ENET_CLIENT_HPP
#define ENET_CLIENT_HPP

#include <string>

#include <enet/enet.h>

#include <Network/Client.hpp>

namespace ENet {

    class Client : public Network::Client {
        ENetHost *_handle = nullptr;
        
        uint32_t _connectTimeout = 10;
    public:
        Client();

        void Connect(const std::string& address, uint16_t port) override;
        Network::ConnectionStatus GetConnectionStatus() override;
    };
}

#endif /* !ENET_CLIENT_HPP */
