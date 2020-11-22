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

#include <Gui/LayoutBuilder.hpp>
#include <Graphics/Shader.hpp>

#include <Graphics/Buffer.hpp>

namespace Graphics {

    class Context;

    using DrawFunc = std::function<void(Context&)>;

    class Context {
    protected:

        template<typename T>
        struct Type {
            size_t hash;
        };

        SDL_Window* _window;

        std::vector<DrawFunc> _drawables;
        
        virtual Graphics::Shader* create(Type<Graphics::Shader> type, const std::string& name) = 0;
        virtual Graphics::Buffer* create(Type<Graphics::Buffer> type, enum BufferType bt, const float *data, size_t size) = 0;
    public:
        static std::shared_ptr<Context> Create(const std::string& name,
                const std::string& title);

        Context(const std::string& title, SDL_WindowFlags flags);
        ~Context();

        glm::ivec2 GetSize() const;
        SDL_Window *GetWindow();

        virtual void HandleInput() = 0;
        virtual bool HandleEvent(SDL_Event& event) = 0;

        virtual void Update(float deltaTime) = 0;

        virtual void Render() = 0;

        virtual size_t AddDrawFunction(DrawFunc func);
        virtual void RemoveDrawFunction(size_t idx);

        virtual void BuildLayout(std::function<void(Gui::LayoutBuilder& b)>) = 0;

        template<typename T, typename... Args>
        T* Create(Args&&... args) {
            Type<T> type;

            type.hash = typeid (T).hash_code();

            return create(type, std::forward<Args>(args)...);
        }
    };
}

#endif /* !GRAPHICS_CONTEXT_HPP */
