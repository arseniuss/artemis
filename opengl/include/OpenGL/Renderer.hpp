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

#include <Common/Dictionary.hpp>
#include <Graphics/Objects/Light.hpp>
#include <Graphics/Renderer.hpp>
#include <Maths/Frustum.hpp>
#include <OpenGL/Background.hpp>
#include <OpenGL/Capabilities.hpp>
#include <OpenGL/Program.hpp>
#include <OpenGL/State.hpp>

namespace OpenGL {

    class Context;
    class RenderItem;

    class Renderer : public Graphics::Renderer {
    private:
        OpenGL::Context& _context;
        OpenGL::Capabilities _capabilities;
        Common::Dictionary _properties;
        State _state;

        glm::mat4 _projMatrix;

        Maths::Frustum _frustum;

        Background background;

        std::map<std::weak_ptr<Graphics::Object>, std::shared_ptr<RenderItem>, std::owner_less<>> _items;

        std::vector<std::weak_ptr<RenderItem>> _transparentObjects;
        std::vector<std::weak_ptr<RenderItem>> _opaqueObject;

        Program _defaultProgram;

        void setupProgram(std::shared_ptr<Graphics::Object> object,
                std::shared_ptr<Graphics::Material> material, Graphics::Camera& camera);
    protected:
        void RenderObject(std::weak_ptr<RenderItem> object, std::shared_ptr<Graphics::Scene> scene,
                std::shared_ptr<Graphics::Camera> camera);
        void RenderObjects(std::vector<std::weak_ptr<RenderItem>> objects, std::shared_ptr<Graphics::Scene> scene,
                std::shared_ptr<Graphics::Camera> camera);
        /**
         * Sort objects
         * @param o
         * @param camera
         */
        void ProjectObject(std::shared_ptr<Graphics::Object> o, std::shared_ptr<Graphics::Camera> camera);

        void Push(Graphics::Object& objects, Graphics::Geometry& geometry, Graphics::Material& material);


        void findProgram();
    public:
        Renderer(OpenGL::Context& ctx);
        ~Renderer();

        void Render(std::shared_ptr<Graphics::Scene> scene, std::shared_ptr<Graphics::Camera> camera) override;
    };
}

#endif /* !OPENGL_RENDERER_HPP */
