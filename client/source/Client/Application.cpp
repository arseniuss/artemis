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
    int mousex, mousey;
    uint32_t mouse, mod;

    while (running) {
        if (_states.empty())
            break;

        State& current = *(State *) _states.back().get();
        SDL_Event event;

        mouse = SDL_GetMouseState(&mousex, &mousey);
        mod = SDL_GetModState();

        //uiSetCursor(mousex, mousey);

        //uiSetButton(0, mod, mouse & SDL_BUTTON_LMASK ? 1 : 0);
        //uiSetButton(1, mod, mouse & SDL_BUTTON_MMASK ? 1 : 0);
        //uiSetButton(2, mod, mouse & SDL_BUTTON_RMASK ? 1 : 0);

        current.HandleInput();

        while (SDL_PollEvent(&event)) {
            current.HandleEvent(event);
        }

        auto stop = timer.now();
        float deltaTime = chrono::duration<float, std::milli>(stop - start).count();
        start = stop;

        current.Update(deltaTime);
        //uiProcess(deltaTime);

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

