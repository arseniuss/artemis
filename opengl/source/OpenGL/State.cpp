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

#include <Graphics/Buffer.hpp>
#include <Graphics/Geometries/BufferGeometry.hpp>
#include <Graphics/Material.hpp>
#include <OpenGL/Binding.hpp>
#include <OpenGL/Program.hpp>
#include <OpenGL/State.hpp>
#include <OpenGL/Debug.hpp>

#include <glad.h>

using namespace OpenGL;

State::State() {

}

bool State::ChangeProgram(std::shared_ptr<Program> program) {
    if (_lastProgram != program) {
        program->Use();
        _lastProgram = program;
        return true;
    }

    return false;
}

void State::SetMaterial(std::shared_ptr<Graphics::Material> material) {
    if (material->GetSides() == Graphics::DOUBLE_SIDED) {
        //GL_CHECK2(glDisable, GL_CULL_FACE);
    } else {
        //GL_CHECK2(glEnable, GL_CULL_FACE);
    }

    // TODO
}

std::shared_ptr<Binding> State::GetBindingState(std::shared_ptr<Graphics::BufferGeometry> geometry,
        std::shared_ptr<Program> program) {
    auto weak_geo = geometry->weak_from_this();

    if (_bindings.contains(weak_geo)) {
        return _bindings[weak_geo];
    }

    auto binding = std::make_shared<Binding>(weak_geo, program);

    _bindings.emplace(geometry, binding);
    Common::RegisterOnDestruct<State, Graphics::BufferGeometry>(this, geometry, [](auto a, auto b) {
        a->Remove(b);
    });

    return binding;
}

void State::Remove(std::weak_ptr<Graphics::BufferGeometry> geometry) {
    DEBUG("Removing geometry");
    if (_bindings.contains(geometry)) {
        _bindings.erase(geometry);
    }
}
