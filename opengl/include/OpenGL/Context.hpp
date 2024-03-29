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
    class Renderer;

    class Context : public Graphics::Context {
    protected:
        std::shared_ptr<OpenGL::Renderer> _renderer;
        SDL_GLContext _context;

        NVG::NVGcontext* _nvgContext;

        void drawLayout(int item, int corners);
    public:
        static bool Debug;
        static std::shared_ptr<Context> Instance;

        Context(const std::string& title, std::shared_ptr<const Common::Config> config);
        ~Context();

        void HandleInput() override;
        bool HandleEvent(SDL_Event& event) override;

        void Update(float deltaTime) override;

        void BuildLayout(std::function<void(Gui::LayoutBuilder&)>) override;

        void DrawLayout();

        std::shared_ptr<Graphics::Renderer> GetRenderer() override;
    };
}

#endif /* !OPENGL_CONTEXT_HPP */

