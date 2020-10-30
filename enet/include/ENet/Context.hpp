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

#ifndef ENET_CONTEXT_HPP
#define ENET_CONTEXT_HPP

#include <Network/Context.hpp>

namespace ENet {

    class Context : public Network::Context {
    protected:
        Network::Host* create(Type<Network::Host> type, int maxConnections) override;
        Network::Client* create(Type<Network::Client> type) override;
    public:

    };
}

#endif /* !ENET_CONTEXT_HPP */
