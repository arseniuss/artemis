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

#include <Graphics/Scene.hpp>

using namespace Graphics;

static unsigned int sceneIndex = 0;

size_t Scene::Hash = typeid(Scene).hash_code();

Scene::Scene() : _background() {
    _name = "Scene #" + std::to_string(sceneIndex++);
    _hash = Scene::Hash;
}

std::weak_ptr<Graphics::Property> Scene::GetBackground() {
    return _background;
}
