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

#ifndef SERVER_ENGINE_HPP
#define SERVER_ENGINE_HPP

#include <atomic>
#include <thread>
#include <vector>

#include <Network/Context.hpp>
#include <Network/Host.hpp>

namespace Server {

    class Engine {
    private:
        std::shared_ptr<Common::Config> _config;
        std::shared_ptr<Network::Context> _net;
        std::thread _serverThread;
        
        std::atomic<bool> _isRunning = false;

        std::vector<std::shared_ptr<Network::Peer>> _pendingConnections;

        

        Engine();

        void main();
        void addPending(std::shared_ptr<Network::Peer> peer);

#define C(_enum) \
        void handle_##_enum(std::shared_ptr<Network::Peer> peer, \
            Network::ServerPayload<Network::_enum> payload);
#include <Network/ServerCommands.inc.hpp>

    public:
        static int maxConnections;
        
        static Engine& Get();

        bool Start();
        bool Stop();

        bool Started() const {
            return _isRunning;
        }
    };
}

#endif /* !SERVER_ENGINE_HPP */
