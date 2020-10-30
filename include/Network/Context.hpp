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

#ifndef NETWORK_CONTEXT_HPP
#define NETWORK_CONTEXT_HPP

#include <memory>

#include <Network/Client.hpp>
#include <Network/Host.hpp>

namespace Network {

    class Context {
    protected:

        template<typename T>
        struct Type {
            size_t hash;
        };

        virtual Network::Host* create(Type<Network::Host> type,
                int maxConnections) = 0;
        virtual Network::Client* create(Type<Network::Client> type) = 0;

        Context() = default;
    public:
        static const uint16_t DefaultPort = 7654;
        
        static std::shared_ptr<Context> Create(const std::string& name);

        template<typename T, typename... Args>
        T* Create(Args&&... args) {
            Type<T> type;

            type.hash = typeid (T).hash_code();

            return create(type, std::forward<Args>(args)...);
        }
    };

}

#endif /* !NETWORK_CONTEXT_HPP */
