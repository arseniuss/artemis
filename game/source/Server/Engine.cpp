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
#include <thread>

#include <Common/Debug.hpp>
#include <Network/Context.hpp>
#include <Network/Event.hpp>
#include <Network/Host.hpp>
#include <Network/Payload.hpp>
#include <Network/Peer.hpp>
#include <Server/Engine.hpp>

using namespace std::chrono_literals;

using namespace Server;

int Engine::maxConnections = 10;

Engine& Engine::Get() {
    static Engine *instance = nullptr;

    if (!instance) instance = new Engine();

    return *instance;
}

Engine::Engine() {

}

bool Engine::Start() {
    if (_isRunning) {
        return false;
    }

    _serverThread = std::thread(&Engine::main, this);

    return true;
}

bool Engine::Stop() {
    _isRunning = false;
    
    _serverThread.join();

    return true;
}

void Engine::main() {
    Network::Event* event = nullptr;

    std::cout << "Starting server ..." << std::endl;
    _config = std::make_shared<Common::Config>("server.yaml");
    _net = Network::Context::Create(_config);
    auto host = _net->Create<Network::Host>(maxConnections);
    
    _isRunning = true;

    while (_isRunning) {
        while (host->PullEvent(&event)) {
            auto peer = event->GetPeer();

            switch (event->GetType()) {
                case Network::Connect:
                    Common::Debug() << "Server: connect" << std::endl;
                    addPending(peer);
                    break;
                case Network::Disconnect:
                case Network::Timeout:
                    break;
                case Network::Data:
                {
                    Network::Payload payload = event->GetPayload();
                    Network::ToServerCommand cmd = payload.GetServerCommand();

                    switch (cmd) {
#define C(_enum)    case Network::_enum: \
                        handle_##_enum(peer, Network::ServerPayload<Network::_enum>(payload)); \
                        break;
#include <Network/ServerCommands.inc.hpp>
#include <vector>
                    }

                    break;
                }
            }

            if (event)
                delete event;
        }
    }

    std::cout << "Quitting server ..." << std::endl;
    delete host;
}

void Engine::addPending(std::shared_ptr<Network::Peer> peer) {
    _pendingConnections.push_back(peer);
}


void Engine::handle_HandshakeRequest(std::shared_ptr<Network::Peer> peer, 
        Network::ServerPayload<Network::HandshakeRequest> payload) {
    for(auto& pendingConnection : _pendingConnections) {
        if(pendingConnection->GetId() == peer->GetId()) {
            Network::ClientPayload<Network::ToClientCommand::HandshakeResponse> rsp;
            
            peer->Send(rsp);
        }
    }
}

