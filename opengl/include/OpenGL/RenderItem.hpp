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

#ifndef OPENGL_RENDERITEM_HPP
#define OPENGL_RENDERITEM_HPP

#include <memory>

#include <OpenGL/Program.hpp>
#include <OpenGL/State.hpp>

#include <glad.h>

namespace Graphics {
    class Object;
    class Material;
    class Camera;
}

namespace OpenGL {

    class RenderItem : public std::enable_shared_from_this<RenderItem> {
    private:
        bool _cached = false;

        GLenum _mode = 0;

        std::shared_ptr<Program> _program;
        State _state;

        bool needsUpdate();

        std::shared_ptr<Program> setProgram(State state, Common::Dictionary& properties,
                std::shared_ptr<Graphics::Camera> camera, std::shared_ptr<Graphics::Material> mat,
                std::shared_ptr<Graphics::Object> obj);
    public:
        std::weak_ptr<Graphics::Object> object;
        std::weak_ptr<Graphics::Material> material;
        std::weak_ptr<Graphics::Geometry> geometry;

        ~RenderItem();

        void Reset(State& state);

        /**
         * Update render item from updated object
         * @param o
         */
        void Update(std::shared_ptr<Graphics::Object> o);

        void Build();

        void Render(State& state, Common::Dictionary& properties, std::shared_ptr<Graphics::Camera> camera);
    };
}

#endif /* !OPENGL_RENDERITEM_HPP */
