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

#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include <Graphics/Renderer.hpp>
#include <Maths/Frustum.hpp>
#include <OpenGL/Renderer.hpp>

namespace OpenGL {

    class Context;
    
    class Renderer : public Graphics::Renderer {
    private:
        OpenGL::Context& _context;
        
        glm::mat4 _projMatrix;
        
        Maths::Frustum _frustum;
    public:
        Renderer(OpenGL::Context& ctx);
        ~Renderer();

        void Begin() override;

        void Render(Graphics::Scene& scene, Graphics::Camera& camera) override;

        void Finish() override;
    };
}

#endif /* !OPENGL_RENDERER_HPP */
