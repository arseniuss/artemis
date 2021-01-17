/**
 *  Artemis game
 *  Copyright (C) 2021 Armands Arseniuss Skolmeisters
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

#ifndef CLIENT_GALAXYSTATE_HPP
#define CLIENT_GALAXYSTATE_HPP

#include <Client/State.hpp>

namespace Client {
    class GalaxyState : public State {
    private:
        Graphics::Scene* _scene;
        Graphics::Camera* _camera;
    public:
        GalaxyState(Application *app);
        
        void BuildUI(Gui::LayoutBuilder& builder) override;
        
        bool HandleEvent(const SDL_Event& event) override;
        
        void Render(Graphics::Renderer& renderer) override;

    };
}

#endif /* !CLIENT_GALAXYSTATE_HPP */
