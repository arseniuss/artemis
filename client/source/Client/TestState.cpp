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
#include <Gui/Window.hpp>

using namespace Client;

TestState::TestState(Application* app) : State(app, "Test state") {

}

void TestState::BuildUI(Gui::LayoutBuilder& builder) {
    auto window1 = builder.Create<Gui::Window>();

    window1->SetSize(100, 200);
    window1->SetTitle("WINDOW1");

    builder.Insert(window1);

    auto window2 = builder.Create<Gui::Window>();

    window2->SetSize(100, 200);
    window2->SetTitle("WINDOW2");

    builder.Insert(window2);
}

void TestState::HandleEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            _app.PopState();
            break;
    }
}

