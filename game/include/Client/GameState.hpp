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

#ifndef CLIENT_GAMESTATE_HPP
#define CLIENT_GAMESTATE_HPP

#include <Client/State.hpp>
#include <Graphics/Camera.hpp>

namespace Client {
    class GameState : public State {
    private:
        Graphics::Camera* _camera;
    public:
        GameState(Application *app);
        virtual ~GameState() = default;
        
        bool HandleEvent(const SDL_Event& event) override;

    };
}

#endif /* !CLIENT_GAMESTATE_HPP */
