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

#include <SDL2/SDL.h>

#include <Common/Application.hpp>
#include <Common/PluginManager.hpp>

using namespace Common;

Application::Application() {
    PluginManager::GetInstance().InitialLoad();
}

Application::~Application() {

}

void Application::PopState() {
    _isPoping = true;
}

void Application::AddLoop(EventCallbackBase<bool>* loop) {
    LoopVectorT::iterator it = std::find(_loops.begin(), _loops.end(), loop);

    if (it != _loops.end()) {
        DEBUG("Loop exists");
        return;
    }
    
    _loops.emplace_back(loop);
}

void Application::RemoveLoop(EventCallbackBase<bool>* loop) {
    LoopVectorT::iterator it = std::find(_loops.begin(), _loops.end(), loop);
    
    if(it != _loops.end()) {
        _loops.erase(it);
    }
}

