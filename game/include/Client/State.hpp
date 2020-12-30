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

#ifndef CLIENT_STATE_HPP
#define CLIENT_STATE_HPP

#include <Common/State.hpp>
#include <Client/Application.hpp>

namespace Client {

    class State : public Common::State {
    protected:
        Application& _app;
        int root;
    public:
        State(Application* app, const std::string& name);

        void OnEnable() override;
        
        virtual void BuildUI(Gui::LayoutBuilder& builder);
        
        void RebuildUI();
        
        virtual bool HandleEvent(const SDL_Event& event);
    };
}

#endif /* !CLIENT_STATE_HPP */

