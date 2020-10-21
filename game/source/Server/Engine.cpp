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

#include <iostream>

#include <Server/Engine.hpp>
#include <thread>

using namespace std::chrono_literals;

using namespace Server;

Engine& Engine::Get() {
    static Engine *instance = nullptr;

    if (!instance) instance = new Engine();

    return *instance;
}

Engine::Engine() {

}

bool Engine::Start() {
    if (_started) {
        return false;
    }

    _started = true;
    _serverThread = std::thread(&Engine::main, this);

    return true;
}

bool Engine::Stop() {
    _started = false;

    _serverThread.join();

    return true;
}

void Engine::main() {
    std::cout << "Starting server ..." << std::endl;

    while (_started) {

    }

    std::cout << "Quitting server ..." << std::endl;
}


