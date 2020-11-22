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

#ifndef CLIENT_CONNECTSTATE_HPP
#define CLIENT_CONNECTSTATE_HPP

#include <Client/State.hpp>
#include <Gui/Text.hpp>

namespace Client {
    class ConnectState : public State {
        Gui::Text *_textInput = nullptr;
    public:
        ConnectState(Application *app);
        virtual ~ConnectState() = default;
        
        void BuildUI(Gui::LayoutBuilder& builder) override;

        bool HandleEvent(const SDL_Event& event) override;

    };
}

#endif /* !CLIENT_CONNECTSTATE_HPP */
