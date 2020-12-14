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

using namespace std;
using namespace Graphics;

typedef void (*InitGraphicsFunc)(void);
typedef Context* (*CreateContextFunc)(const string&);

shared_ptr<Context> Context::Create(const string& name, const string& title) {
    string target = "lib/libartemis_" + name + ".so";
    void *handle = dlopen(target.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!handle) {
        throw runtime_error(string("Cannot open " + target + ": " + dlerror()));
    }

    InitGraphicsFunc init = (InitGraphicsFunc) dlsym(handle, "InitGraphics");

    if (init != nullptr) {
        init();
    }

    CreateContextFunc func = (CreateContextFunc) dlsym(handle, "CreateContext");

    if (func == nullptr) {
        throw runtime_error("Graphic's function \"CreateContext\" not found!");
    }

    return shared_ptr<Context>(func(title));
}

Context::Context(const std::string& title, SDL_WindowFlags flags) {
    SDL_DisplayMode current;
    int use_window = -1;

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        throw runtime_error(string("Cannot init SDL video: ") + SDL_GetError());
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
        throw runtime_error(string("Cannot find display!"));
    }

    IMG_Init(IMG_INIT_PNG);

    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, current.w, current.h,
            flags | SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);
    if (_window == nullptr) {
        throw runtime_error("Cannot create window!");
    }
}

Context::~Context() {

}

glm::ivec2 Context::GetSize() const {
    int w, h;

    SDL_GetWindowSize(_window, &w, &h);

    return {w, h};
}

size_t Context::AddDrawFunction(DrawFunc func) {
    _drawables.emplace_back(func);

    return _drawables.size();
}

void Context::RemoveDrawFunction(size_t idx) {
    _drawables.erase(_drawables.begin() + idx);
}
