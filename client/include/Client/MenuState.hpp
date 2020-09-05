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

#ifndef CLIENT_MENUSTATE_HPP
#define CLIENT_MENUSTATE_HPP

#include <Client/State.hpp>
#include <Client/Application.hpp>

namespace Client {

    class MenuState : public State {
    public:
        MenuState(Application* app);
        virtual ~MenuState() = default;

        void BuildUI(Gui::LayoutBuilder& builder) override;

        void HandleEvent(const SDL_Event& event) override;
    };
}

#endif /* !CLIENT_MENUSTATE_HPP */

