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

#include "Test.hpp"

using namespace TestingFramework;

void loop() {
    std::shared_ptr<Common::Config> config = std::make_shared<Common::Config>("config.yaml");
    std::shared_ptr<Graphics::Context> graphics = Graphics::Context::Create(config);
    std::shared_ptr<Graphics::Renderer> renderer = graphics->GetRenderer();

    bool running = true;
    SDL_Event event;

    TestVector::iterator testIt = Tests.begin();

    DEBUG("Test count " << Tests.size());
    if (testIt != Tests.end()) {
        (*testIt)->Init(graphics);
    }

    while (running) {
        graphics->HandleInput();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    DEBUG("Deinit last test");
                    (*testIt)->Deinit();
                    DEBUG("Moving to next test");
                    testIt++;
                    if (testIt != Tests.end()) {
                        DEBUG("Next test name is " << (*testIt)->GetName());
                        (*testIt)->Init(graphics);
                    }
                }
            }

            graphics->HandleEvent(event);
        }

        if (testIt == Tests.end()) {
            DEBUG("Testing done");
            running = false;
        } else {
            auto scene = (*testIt)->GetScene();
            auto camera = (*testIt)->GetCamera();

            renderer->Render(scene, camera);
        }
    }

    Tests.clear();
}

int main(int argc, char** argv) {
    loop();

    DEBUG("Testing is done!");

    return 0;
}


