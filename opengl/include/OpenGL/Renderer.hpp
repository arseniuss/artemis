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

#include <map>

#include <Graphics/Objects/Light.hpp>
#include <Graphics/Renderer.hpp>
#include <Maths/Frustum.hpp>
#include <OpenGL/Capabilities.hpp>
#include <OpenGL/RenderItem.hpp>
#include <OpenGL/Renderer.hpp>

namespace OpenGL {

    class Context;

    class Renderer : public Graphics::Renderer {
    private:
        OpenGL::Context& _context;
        OpenGL::Capabilities _capabilities;

        glm::mat4 _projMatrix;

        Maths::Frustum _frustum;

        std::map<std::weak_ptr<Graphics::Object>, std::shared_ptr<RenderItem>, std::owner_less<>> _items;
        std::vector<std::weak_ptr<Graphics::Light>> _lights;
        std::vector<std::weak_ptr<Graphics::Light>> _shadows;
    protected:
        void RenderObject(Graphics::Object& object, Graphics::Scene& scene, Graphics::Camera& camera,
                Graphics::Geometry& geo, Graphics::Material& mat) override;
        void ProjectObject(std::shared_ptr<Graphics::Object> o, 
            std::shared_ptr<Graphics::Camera> camera,
            int groupOrder, bool sortObjects);

        void Push(Graphics::Object& objects,
                Graphics::Geometry& geometry,
                Graphics::Material& material,
                int groupOrder,
                float z,
                Graphics::Group* group
                );
    public:
        Renderer(OpenGL::Context& ctx);
        ~Renderer();

        void Begin() override;

        void Render(std::shared_ptr<Graphics::Scene> scene, std::shared_ptr<Graphics::Camera> camera) override;

        void Finish() override;
    };
}

#endif /* !OPENGL_RENDERER_HPP */
