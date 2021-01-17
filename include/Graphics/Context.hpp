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

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include <Common/Config.hpp>
#include <Graphics/Renderer.hpp>
#include <Gui/LayoutBuilder.hpp>

namespace Graphics {

    class Context;

    typedef void (*InitGraphicsFunc)(void);
    typedef std::shared_ptr<Context> (*CreateContextFunc)(const std::string&,
            std::shared_ptr<const Common::Config> config);

    class Context {
    protected:

        template<typename T>
        struct Type {
            size_t hash;
        };

        SDL_Window* _window;
    public:
        static std::shared_ptr<Context> Create(std::shared_ptr<const Common::Config> config);

        Context(const std::string& title,
                std::shared_ptr<const Common::Config> config,
                SDL_WindowFlags flags);
        ~Context();

        glm::ivec2 GetSize() const;
        SDL_Window *GetWindow();

        virtual void HandleInput() = 0;
        virtual bool HandleEvent(SDL_Event& event) = 0;

        virtual void Update(float deltaTime) = 0;

        virtual void BuildLayout(std::function<void(Gui::LayoutBuilder& b)>) = 0;

        template<typename T, typename... Args>
        T* Create(Args&&... args) {
            Type<T> type;

            type.hash = typeid (T).hash_code();

            return create(type, std::forward<Args>(args)...);
        }
        
        virtual std::shared_ptr<Graphics::Renderer> GetRenderer() = 0;
    };
}

#endif /* !GRAPHICS_CONTEXT_HPP */
