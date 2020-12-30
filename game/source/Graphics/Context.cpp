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

#include <dlfcn.h>

#include <iostream>

#include <SDL2/SDL_image.h>

#include <Graphics/Context.hpp>

using namespace Graphics;

std::shared_ptr<Context> Context::Create(std::shared_ptr<const Common::Config> config) {
    std::string name = config->Get<std::string>("Graphics", "Library", "opengl");
    std::string target = "lib/libartemis_" + name + ".so";
    void *handle = dlopen(target.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!handle) {
        throw std::runtime_error(std::string("Cannot open " + target + ": " + dlerror()));
    }

    InitGraphicsFunc init = **(InitGraphicsFunc*) dlsym(handle, "initGraphics");

    if (init != nullptr) {
        init();
    }

    CreateContextFunc func = **(CreateContextFunc*) dlsym(handle, "createContext");

    if (func == nullptr) {
        throw std::runtime_error("Graphic's function \"CreateContext\" not found!");
    }

    return func("Artemis", config);
}

Context::Context(const std::string& title,
        std::shared_ptr<const Common::Config> config, SDL_WindowFlags flags) {
    SDL_DisplayMode current;
    int use_window = -1;

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(std::string("Cannot init SDL video: ") + SDL_GetError());
    }

    for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
        int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

        if (should_be_zero != 0) {
            std::cout << "Couldn't get display mode for video display #" << i
                    << ": " << SDL_GetError() << std::endl;
        } else {
            std::cout << "Display #" << i << ": current display mode is " <<
                    current.w << "x" << current.h << "@" <<
                    current.refresh_rate << std::endl;
            if (use_window < 0) use_window = i;
        }
    }

    if (use_window < 0) {
        throw std::runtime_error(std::string("Cannot find display!"));
    }

    IMG_Init(IMG_INIT_PNG);

    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, current.w, current.h, flags);
    if (_window == nullptr) {
        throw std::runtime_error("Cannot create window!");
    }
}

Context::~Context() {

}

glm::ivec2 Context::GetSize() const {
    int w, h;

    SDL_GetWindowSize(_window, &w, &h);

    return {w, h};
}

SDL_Window* Context::GetWindow() {
    return _window;
}

size_t Context::AddDrawFunction(DrawFunc func) {
    _drawables.emplace_back(func);

    return _drawables.size();
}

void Context::RemoveDrawFunction(size_t idx) {
    _drawables.erase(_drawables.begin() + idx);
}
