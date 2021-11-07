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

#ifndef NETWORK_HOST_HPP
#define NETWORK_HOST_HPP

#include <Network/Event.hpp>

namespace Network {

    class Host {
    public:
        Host() = default;

        Host(int maxConnections) {
        }

        virtual ~Host() = default;

        virtual bool PullEvent(Network::Event** event) = 0;
    };
}

#endif /* !NETWORK_HOST_HPP */
