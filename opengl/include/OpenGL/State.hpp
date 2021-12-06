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

#include <OpenGL/Capabilities.hpp>

namespace Graphics {
    class BaseBuffer;
    class BufferGeometry;
    class Camera;
    class Material;
    class Texture;
}

namespace OpenGL {
    class Binding;
    class Program;
    class Texture;

    using MappingMap = std::map<std::string, std::pair<std::shared_ptr<Graphics::BaseBuffer>, int>>;
    using BindingMap = std::map<std::weak_ptr<Graphics::BufferGeometry>, std::shared_ptr<Binding>, std::owner_less<>>;
    using TextureMap = std::map<std::weak_ptr<Graphics::Texture>, std::shared_ptr<Texture>, std::owner_less<>>;

    class State : public std::enable_shared_from_this<State> {
        Capabilities& _capabilities;

        float _lineWidth;

        std::shared_ptr<Graphics::Camera> _camera;
        std::shared_ptr<Program> _lastProgram;

        BindingMap _bindings;
        TextureMap _textures;

        std::vector<std::weak_ptr<Texture>> _textureBindings;
    public:
        State(Capabilities& caps);

        bool ChangeProgram(std::shared_ptr<Program> program);

        float GetLineWidth() const;
        void SetLineWidth(float lineWidth);

        std::shared_ptr<Graphics::Camera> GetCamera();
        void SetCamera(std::shared_ptr<Graphics::Camera> camera);

        void SetMaterial(std::shared_ptr<Graphics::Material> material);

        std::shared_ptr<Texture> GetTexture(std::shared_ptr<Graphics::Texture> texture);
        int BindTexture(std::shared_ptr<Texture> texture);

        std::shared_ptr<Binding> GetBindingState(std::shared_ptr<Graphics::BufferGeometry> geometry,
                std::shared_ptr<Program> program);
    };
}

#endif /* !OPENGL_STATE_HPP */
