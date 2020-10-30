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

#include <Network/Context.hpp>

using namespace Network;

typedef void (*InitNetworkingFunc)(void);
typedef Context* (*CreateContextFunc)(void);

std::shared_ptr<Context> Context::Create(const std::string& name) {
    std::string target = "lib/libartemis_" + name + ".so";
    void *handle = dlopen(target.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!handle) {
        throw std::runtime_error(std::string("Cannot open " + target + ": " + dlerror()));
    }

    InitNetworkingFunc init = (InitNetworkingFunc) dlsym(handle, "InitNetworking");

    if (init != nullptr) {
        init();
    }

    CreateContextFunc func = (CreateContextFunc) dlsym(handle, "CreateContext");

    if (func == nullptr) {
        throw std::runtime_error("Networking function \"CreateCOntext\" not found!");
    }

    return std::shared_ptr<Context>(func());
}
