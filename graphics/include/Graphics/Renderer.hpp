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

#ifndef GRAPHICS_RENDERER_HPP
#define GRAPHICS_RENDERER_HPP

#include <Graphics/Camera.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Scene.hpp>

namespace Graphics {

    class Renderer {
    protected:
        
    public:

        virtual void Render(std::shared_ptr<Graphics::Scene> scene, std::shared_ptr<Graphics::Camera> camera) = 0;
    };
}

#endif /* !GRAPHICS_RENDERER_HPP */
