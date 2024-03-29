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

#include <Gui/Widget.hpp>
#include <Gui/Layout.hpp>

#include "Client/State.hpp"
#include "Client/Application.hpp"

using namespace Client;

State::State(Application* app, const std::string& name) :
Common::State(app, name), _app(*app) {
    
}

void State::OnEnable() {
    _app.GetContext().BuildLayout([this](Gui::LayoutBuilder & b) {
        this->BuildUI(b);
    });
}

void State::BuildUI(Gui::LayoutBuilder& builder) {

}

void State::RebuildUI() {
    _app.GetContext().BuildLayout([this](Gui::LayoutBuilder & b) {
        this->BuildUI(b);
    });
}

bool State::HandleEvent(const SDL_Event& event) {
    return false;
}

void State::Render(Graphics::Renderer& renderer) {
    renderer.Render(nullptr, nullptr);
}

