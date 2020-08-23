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
#include <Gui/Oui.hpp>
#include <Client/TestState.hpp>

using namespace Client;

MenuState::MenuState(Application* app) : State(app, "Menu state") {

}

MenuState::~MenuState() {

}

void MenuState::OnPush() {
    OnEnable();
}

void MenuState::OnEnable() {
    uiBeginLayout();

    int root = uiItem();
    auto windowSize = _app.GetGraphics().GetSize();

    uiSetSize(root, windowSize.x, windowSize.y);
    uiSetBox(root, UI_COLUMN);

    int layout1 = Gui::CreatePanel();
    uiSetLayout(layout1, UI_CENTER);
    uiSetBox(layout1, UI_COLUMN);
    uiSetMargins(layout1, 0, 0, 0, 0);
    uiSetSize(layout1, 200, 200);

    uiInsert(root, layout1);

    int button1 = Gui::CreateButton(-1, "BEGIN", nullptr);
    uiSetLayout(button1, UI_HFILL | UI_TOP);
    uiSetMargins(button1, 0, 1, 0, 0);

    uiInsert(layout1, button1);

    int testButton = Gui::CreateButton(-1, "TEST",
            [this](int item, UIevent event) {
                _app.PushState<TestState>(&_app);
            });
    uiSetLayout(testButton, UI_HFILL | UI_TOP);
    uiSetMargins(testButton, 0, 1, 0, 0);

    uiInsert(layout1, testButton);

    auto e = std::bind(&MenuState::onExitButton, this, std::placeholders::_1, std::placeholders::_2);

    int button2 = Gui::CreateButton(-1, "EXIT", e);
    uiSetLayout(button2, UI_HFILL | UI_TOP);
    uiSetMargins(button2, 0, 1, 0, 0);

    uiInsert(layout1, button2);

    uiEndLayout();
}

void MenuState::onExitButton(int item, UIevent event) {
    _app.PopState();
}

void MenuState::HandleInput() {

}

void MenuState::HandleEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            _app.PopState();
            break;
    }
}
