/**
 *  Artemis game
 *  Copyright (C) 2020 Armands Arseniuss Skolmeisters
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

#ifndef OPENGL_CONTEXT_HPP
#define OPENGL_CONTEXT_HPP

#include <Graphics/Buffer.hpp>
#include <Graphics/Context.hpp>
#include <NanoVG/NanoVG.hpp>

namespace OpenGL {

    class Context : public Graphics::Context {
    protected:
        SDL_GLContext _context;

        NVG::NVGcontext* _nvgContext;

        Graphics::Shader* create(Type<Graphics::Shader> type,
                const std::string& name) override;
        Graphics::Buffer* create(Type<Graphics::Buffer> type,
                Graphics::BufferType bt, const float* data,
                size_t size) override;

    public:
        Context(const std::string& title);
        ~Context();

        void HandleInput() override;
        bool HandleEvent(SDL_Event& event) override;

        void Update(float deltaTime) override;

        void Render() override;

        void BuildLayout(std::function<void(Gui::LayoutBuilder&)>) override;

        void DrawLayout(int item, int corners);
    };
}

#endif /* !OPENGL_CONTEXT_HPP */

