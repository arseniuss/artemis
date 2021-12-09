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

#ifndef UI_FREEMOVEMENTHANDLER_HPP
#define UI_FREEMOVEMENTHANDLER_HPP

#include <memory>

#include <glm/glm.hpp>

#include <SDL2/SDL_events.h>

namespace Graphics {
    class Object;
    class Context;
}

namespace Ui {

    class FreeMovementHandler {
    private:
        std::shared_ptr<Graphics::Object> _target;
        
        float _speed;
        
        float _sensitivity;
        float _yaw;
        float _pitch;
    public:
        FreeMovementHandler();
        
        void Init(std::shared_ptr<Graphics::Context> context);
        void Deinit();

        void Attach(std::shared_ptr<Graphics::Object> object);

        bool HandleEvent(const SDL_Event& event);

        void Update(float deltaTime);
    };
}

#endif /* !UI_FREEMOVEMENTHANDLER_HPP */
