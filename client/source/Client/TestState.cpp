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

#include <Client/TestState.hpp>
#include <Gui/Oui.hpp>

#include "oui.h"

using namespace Client;

TestState::TestState(Application* app) : State(app, "Test state") {

}

TestState::~TestState() {

}

void TestState::OnPush() {
    uiBeginLayout();

    int root = uiItem();
    auto windowSize = _app.GetGraphics().GetSize();

    uiSetSize(root, windowSize.x, windowSize.y);
    uiSetBox(root, UI_COLUMN);

    int window1 = Gui::CreateWindow(-1, "Window 1");
    uiSetSize(window1, 100, 200);
    uiInsert(root, window1);

    int window2 = Gui::CreateWindow(-1, "Window 2");
    uiSetSize(window2, 100, 200);
    uiInsert(root, window2);

    uiEndLayout();
}

void TestState::HandleEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            _app.PopState();
            break;
    }
}

