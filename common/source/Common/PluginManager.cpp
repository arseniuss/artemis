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
#include <experimental/filesystem>
#include <iostream>
#include <string>

#include <Common/PluginManager.hpp>

using namespace std::experimental;

using namespace Common;

typedef void (*LoadPluginFunc)(void);

PluginManager::PluginManager() {

}

PluginManager& PluginManager::GetInstance() {
    static PluginManager instance;

    return instance;
}

void PluginManager::InitialLoad() {
    std::string prefix = "libartemis_";
    std::string path = "plugins";

    for (auto& entry : filesystem::directory_iterator(path)) {
        std::string filename = entry.path().filename();

        if (filename.substr(0, prefix.size()) == prefix) {
            try {
                Load(entry.path());
            } catch (std::runtime_error& e) {
                std::cerr << "Load plugin error: " << e.what() << std::endl;
            }
        }
    }
}

void PluginManager::Load(const std::string& filename) {
    void* handle = dlopen(filename.c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!handle) {
        throw std::runtime_error("Cannot open plugin " + filename + ":" + dlerror());
    }

    LoadPluginFunc func = (LoadPluginFunc) dlsym(handle, "LoadPlugin");
    if (!func) {
        throw std::runtime_error("Plugin " + filename + " load function not found!");
    }

    func();
}
