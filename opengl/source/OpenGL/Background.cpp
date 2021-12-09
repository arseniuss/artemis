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

#include <Common.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/CubeTexture.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Scene.hpp>
#include <Graphics/Texture.hpp>
#include <OpenGL/Background.hpp>
#include <OpenGL/Debug.hpp>

#include <glad.h>

using namespace OpenGL;

void Background::clearColor(Graphics::Color color) {
    GL_CHECK2(glClearColor, color.r, color.g, color.b, color.a);
}

void Background::clear() {
    GL_CHECK2(glEnable, GL_DEPTH_TEST);
    //GL_CHECK2(glDepthFunc, GL_LESS);
    GL_CHECK2(glClear, (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

Background::Background() : _clearColor(Graphics::Color::Rgb(0x000000)) {

}

void Background::Render(std::shared_ptr<Graphics::Scene> scene) {
    bool hasBackground = false;
    std::shared_ptr<Graphics::Property> background;
    bool forceClear = true;

    if (scene.get()) {
        auto w = scene->GetBackground();

        if (background = w.lock()) {
            hasBackground = true;
        }
    }

    if (!hasBackground) {
        clearColor(_clearColor);
    } else {
        size_t h = background->GetHash();

        if (h == Graphics::Color::Hash) {
            std::shared_ptr<Graphics::Color> color = std::static_pointer_cast<Graphics::Color>(background);

            clearColor(*color.get());
        } else if (h == Graphics::CubeTexture::Hash) {
            // TODO
        } else if (h == Graphics::Texture::Hash) {
            // TODO
        }


    }

    if (forceClear) {
        clear();
    }
}
