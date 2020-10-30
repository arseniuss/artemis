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

#include <Network/Context.hpp>
#include <Network/Host.hpp>

namespace Server {

    class Engine {
    private:
        std::atomic<bool> _isRunning = false;

        std::thread _serverThread;

        std::shared_ptr<Network::Context> _net;
        Network::Host *_host;

        Engine();

        void main();

#define C(_enum) \
        void handle_##_enum(Network::ServerPayload<Network::_enum> payload);
#include <Network/ServerCommands.inc.hpp>

    public:
        static Engine& Get();

        bool Start();
        bool Stop();

        bool Started() const {
            return _isRunning;
        }
    };
}

#endif /* !SERVER_ENGINE_HPP */
