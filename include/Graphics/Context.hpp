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

#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <glm/vec2.hpp>

#include <SDL2/SDL_video.h>

#include <Gui/LayoutBuilder.hpp>

namespace Graphics {

    class Context;

    using DrawFunc = std::function<void(Context&)>;

    class Context {
    protected:
        SDL_Window* _window;

        std::vector<DrawFunc> _drawables;
    public:
        static std::shared_ptr<Context> Create(const std::string& name,
                const std::string& title);

        Context(const std::string& title, SDL_WindowFlags flags);
        ~Context();
        
        glm::ivec2 GetSize() const;
        SDL_Window *GetWindow();
        
        virtual void HandleInput() = 0;
        
        virtual void Update(float deltaTime) = 0;

        virtual void Render() = 0;
        
        virtual void Draw(DrawFunc func);
        
        virtual void BuildLayout(std::function<void(Gui::LayoutBuilder& b)>) = 0;
    };
}

#endif /* !GRAPHICS_CONTEXT_HPP */
