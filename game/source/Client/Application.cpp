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

#include <chrono>

#include <SDL2/SDL.h>

#include <Client/Application.hpp>
#include <Client/State.hpp>

using namespace std;

using namespace Client;

Application::Application() : Common::Application() {
    _config = std::make_shared<Common::Config>("config.yaml");
    _graphics = Graphics::Context::Create(_config);
    _net = Network::Context::Create(_config);
}

Application::~Application() {
    SDL_Quit();
}

Graphics::Context& Application::GetContext() {
    return *_graphics;
}

void Application::Run() {
    std::chrono::high_resolution_clock timer;
    bool running = true;
    auto start = timer.now();
    auto renderer = _graphics->GetRenderer();

    while (running) {
        if (_states.empty())
            break;

        State* current = (State *) _states.back().get();
        SDL_Event event;

        _graphics->HandleInput();

        current->HandleInput();

        while (SDL_PollEvent(&event)) {
            if (!current->HandleEvent(event)) {
                _graphics->HandleEvent(event);
            }
        }

        auto stop = timer.now();
        float deltaTime = chrono::duration<float, std::milli>(stop - start).count();

        _loops.erase(
                std::remove_if(
                _loops.begin(),
                _loops.end(),
                [](auto* e) {
                    return (*e)();
                }
        ),
        _loops.end());

        start = stop;

        current->Update(deltaTime);
        _graphics->Update(deltaTime);

        current->Render(*renderer);

        if (_isPoping) {
            Common::Debug() << "Poping state " << current->GetName() <<
                    std::endl;
            if (_replaceState)
                current->OnDisable();
            current->OnPop();
            _loops.erase(
                    std::remove_if(
                    _loops.begin(),
                    _loops.end(),
                    [current](auto* e) {
                        return e->is(current);
                    }
            ),
            _loops.end());
            
            current->OnDisable();
            _states.pop_back();
            
            // NOTE. current is unuseable after here
            
            if (_replaceState) {                
                Common::Debug() << "Replacing state " <<
                        _replaceState->GetName() << std::endl;

                _states.push_back({});
                _states.back().swap(_replaceState);
                
                auto replace = _states.back().get();
                
                replace->OnPush();
                
                _replaceState = nullptr;

            } else {
                if (_states.size()) {
                    auto&c = _states.back();

                    c->OnEnable();
                }
            }
            _isPoping = false;
        }
    }
}

