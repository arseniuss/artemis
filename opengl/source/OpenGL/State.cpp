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
#include <Graphics/Texture.hpp>
#include <OpenGL/Binding.hpp>
#include <OpenGL/Debug.hpp>
#include <OpenGL/Program.hpp>
#include <OpenGL/State.hpp>
#include <OpenGL/Texture.hpp>

#include <glad.h>

using namespace OpenGL;

State::State(Capabilities& caps) : _capabilities(caps) {
    _textureBindings.resize(_capabilities.GetMaxCombinedTextures());
}

bool State::ChangeProgram(std::shared_ptr<Program> program) {
    if (_lastProgram != program) {
        program->Use();
        _lastProgram = program;
        return true;
    }

    return false;
}

float State::GetLineWidth() const {
    return _lineWidth;
}

void State::SetLineWidth(float lineWidth) {
    _lineWidth = lineWidth;
}

std::shared_ptr<Graphics::Camera> State::GetCamera() {
    return _camera;
}

void State::SetCamera(std::shared_ptr<Graphics::Camera> camera) {
    _camera = camera;
}

void State::SetMaterial(std::shared_ptr<Graphics::Material> material) {
    if (material->GetSides() == Graphics::DOUBLE_SIDED) {
        //GL_CHECK2(glDisable, GL_CULL_FACE);
    } else {
        //GL_CHECK2(glEnable, GL_CULL_FACE);
    }

    // TODO
}

std::shared_ptr<Texture> State::GetTexture(std::shared_ptr<Graphics::Texture> texture) {
    std::shared_ptr<Texture> ret;
    auto weak_tex = std::weak_ptr(texture);
    auto it = _textures.find(weak_tex);

    if (it == _textures.end()) {
        ret = std::make_shared<Texture>(texture);

        _textures.emplace(texture, ret);
        texture->OnDestruct([this, weak_tex](Common::Observable * o) {
            DEBUG("Removing texture");
            this->_textures.erase(weak_tex);
        });
    } else {
        ret = it->second;
    }

    return ret;
}

int State::BindTexture(std::shared_ptr<Texture> texture) {
    for (size_t i = 0; i < _textureBindings.size(); i++) {
        std::weak_ptr<Texture>& binding = _textureBindings[i];

        if (binding.expired()) {
            std::weak_ptr<Texture> weak_tex = texture;

            binding = texture;

            texture->OnDestruct([i, &binding](Common::Observable*) {
                DEBUG("Removing texture binding");
                
                binding.reset();
            });
            
            glActiveTexture(GL_TEXTURE0 + i);
            // TODO: defferentiate textures
            glBindTexture(GL_TEXTURE_2D, texture->GetId());
            return i;
        }
    }

    return -1;
}

std::shared_ptr<Binding> State::GetBindingState(std::shared_ptr<Graphics::BufferGeometry> geometry,
        std::shared_ptr<Program> program) {
    auto weak_geo = std::weak_ptr(geometry);

    if (_bindings.contains(weak_geo)) {
        return _bindings[weak_geo];
    }

    auto binding = std::make_shared<Binding>(weak_geo, program);

    _bindings.emplace(geometry, binding);
    geometry->OnDestruct([this, weak_geo](Common::Observable * o) {
        DEBUG("Removing geometry");
        this->_bindings.erase(weak_geo);
    });

    return binding;
}
