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

#ifndef OPENGL_STATE_HPP
#define OPENGL_STATE_HPP

#include <memory>

namespace Graphics {
    class Camera;
    class Geometry;
    class Material;
    class Buffer;
}

namespace OpenGL {
    class Program;
    class Binding;

    using MappingMap = std::map<std::string, std::pair<std::shared_ptr<Graphics::Buffer>, int>>;
    using BindingMap = std::map<std::weak_ptr<Graphics::Geometry>, std::shared_ptr<Binding>, std::owner_less<>>;

    class State : public std::enable_shared_from_this<State> {
        float _lineWidth;

        std::shared_ptr<Graphics::Camera> _camera;
        std::shared_ptr<Program> _lastProgram;

        BindingMap _bindings;
    public:
        State();

        bool ChangeProgram(std::shared_ptr<Program> program);

        float GetLineWidth() const {
            return _lineWidth;
        }

        void SetLineWidth(float lineWidth) {
            _lineWidth = lineWidth;
        }

        std::shared_ptr<Graphics::Camera> GetCamera() {
            return _camera;
        }

        void SetCamera(std::shared_ptr<Graphics::Camera> camera) {
            _camera = camera;
        }

        void SetMaterial(std::shared_ptr<Graphics::Material> material);


        std::shared_ptr<Binding> GetBindingState(std::shared_ptr<Graphics::Geometry> geometry);
        void Remove(std::weak_ptr<Graphics::Geometry> geometry);
    };
}

#endif /* !OPENGL_STATE_HPP */
