/**
 *  Artemis game
 *  Copyright (C) 2021 Armands Arseniuss Skolmeisters
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

#include <memory>

#include <Common/Config.hpp>
#include <Graphics/Context.hpp>

int main(int argc, char** argv) {
    std::shared_ptr<Common::Config> config = std::make_shared<Common::Config>("config.yaml");
    std::shared_ptr<Graphics::Context> graphics = Graphics::Context::Create(config);
    std::shared_ptr<Graphics::Renderer> renderer = graphics->GetRenderer();

    bool running = true;
    SDL_Event event;

    while (running) {
        graphics->HandleInput();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }

            graphics->HandleEvent(event);
        }

        renderer->Render(nullptr, nullptr);
    }


    return 0;
}


