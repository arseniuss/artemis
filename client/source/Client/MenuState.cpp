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

using namespace Client;

static void UIHandler(int item, UIevent event) {
    Gui::UIData *data = (Gui::UIData *)uiGetHandle(item);

    if (data && data->handler) {
        data->handler(item, event);
    }
}

MenuState::MenuState(Application* app) : State(app, "Menu state") {
    UIcontext * ctx = uiCreateContext(4096, 1 << 20);

    uiMakeCurrent(ctx);
    uiSetHandler(UIHandler);
}

MenuState::~MenuState() {

}

void MenuState::OnPush() {
    uiBeginLayout();

    int root = Gui::Panel();
    auto windowSize = _app.GetGraphics().GetSize();

    uiSetSize(root, windowSize.x, windowSize.y);
    uiSetBox(root, UI_COLUMN);

    uiEndLayout();
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
