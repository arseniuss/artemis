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

#include "Client/SettingState.hpp"

using namespace Client;

SettingState::SettingState(Application* app) : State(app, "Setting state") {

}

void SettingState::BuildUI(Gui::LayoutBuilder& builder) {
    auto panel = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_CENTER)
            ->SetBox(BOX_COLUMN)
            ->SetMargins(0, 0, 0, 0)
            ->SetSize(700, 500);

    builder.Insert(panel);
}

void SettingState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                _app.PopState();
                break;
        }
    }
}
