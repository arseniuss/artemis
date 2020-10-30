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
    _graphics = Graphics::Context::Create("opengl", "Artemis");
    _net = Network::Context::Create("enet");
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

    while (running) {
        if (_states.empty())
            break;

        State& current = *(State *) _states.back().get();
        SDL_Event event;

        _graphics->HandleInput();

        current.HandleInput();

        while (SDL_PollEvent(&event)) {
            current.HandleEvent(event);
        }

        auto stop = timer.now();
        float deltaTime = chrono::duration<float, std::milli>(stop - start).count();

        auto it = _loops.begin();
        for (; it != _loops.end(); it++) {
            LoopFunc func = *it;

            if (func())
                _loops.erase(it);
        }

        start = stop;

        current.Update(deltaTime);
        _graphics->Update(deltaTime);

        _graphics->Render();

        if (_isPoping) {
            current.OnPop();

            _states.pop_back();
            if (_states.size()) {
                auto&c = _states.back();

                c->OnEnable();
            }
            _isPoping = false;
        }
    }
}

void Application::AddLoop(LoopFunc loopFunc) {
    _loops.emplace_back(loopFunc);
}
