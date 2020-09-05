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

#include <Client/MenuState.hpp>
#include <Client/TestState.hpp>
#include <Client/GameState.hpp>
#include <Gui/Panel.hpp>
#include <Gui/Button.hpp>

using namespace Client;

MenuState::MenuState(Application* app) : State(app, "Menu state") {

}

void MenuState::BuildUI(Gui::LayoutBuilder& builder) {
    auto panel = builder.Create<Gui::Panel>();

    panel->SetLayout(LAYOUT_CENTER);
    panel->SetBox(BOX_COLUMN);
    panel->SetMargins(0, 0, 0, 0);
    panel->SetSize(200, 200);

    builder.Insert(panel);

    auto startGameButton = builder.Create<Gui::Button>();

    startGameButton->SetLabel("BEGIN");
    startGameButton->OnClick([this]() {
        _app.PushState<GameState>(&_app);
    });
    startGameButton->SetLayout(LAYOUT_HFILL | LAYOUT_TOP);
    startGameButton->SetMargins(0, 1, 0, 0);

    panel->Insert(startGameButton);

    auto testButton = builder.Create<Gui::Button>();

    testButton->SetLabel("TEST");
    testButton->OnClick([this]() {
        _app.PushState<TestState>(&_app);
    });
    testButton->SetLayout(LAYOUT_HFILL | LAYOUT_TOP);
    testButton->SetMargins(0, 1, 0, 0);

    panel->Insert(testButton);

    auto exitButton = builder.Create<Gui::Button>();

    exitButton->SetLabel("EXIT");
    exitButton->OnClick([this]() {
        _app.PopState();
    });
    exitButton->SetLayout(LAYOUT_HFILL | LAYOUT_TOP);
    exitButton->SetMargins(0, 1, 0, 0);

    panel->Insert(exitButton);
}

void MenuState::HandleEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            _app.PopState();
            break;
    }
}
