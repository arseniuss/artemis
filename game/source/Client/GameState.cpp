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


#include <Gui/Gui.hpp>
#include <Gui/Panel.hpp>
#include <Gui/Widget.hpp>

#include "Client/GameState.hpp"

using namespace Client;

GameState::GameState(Application *app) : State(app, "Game state") {
    _camera = new Graphics::Camera();
}

void GameState::BuildUI(Gui::LayoutBuilder& builder) {
    auto panel = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_FILL)
            ->SetBox(BOX_LAYOUT)
            ->SetIsVisible(false)

            ;
    builder.Insert(panel);

    auto topPanel = builder.Create<Gui::Panel>()
            ->SetMargins(5, 5, 5, 0)
            ->SetBox(BOX_ROW)
            ->SetIsVisible(false)
            ->SetDebug(true)
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ;
    panel->Insert(topPanel);

    auto leftPanel = builder.Create<Gui::Panel>()
            ->SetSize(100, -1);
    topPanel->Insert(leftPanel);

    auto rightWrapPnl = builder.Create<Gui::Panel>()
            ->SetIsVisible(false)
            ->SetLayout(LAYOUT_HFILL)
            ;
    topPanel->Insert(rightWrapPnl);

    auto centerPanel = builder.Create<Gui::Panel>()
            ->SetSize(100, -1);
    topPanel->Insert(centerPanel);
    
    auto leftWrapPanel = builder.Create<Gui::Panel>()
            ->SetIsVisible(false)
            ->SetLayout(LAYOUT_HFILL)
            ;
    topPanel->Insert(leftWrapPanel);

    auto helpBtn = builder.Create<Gui::Button>()
            ->SetIcon((1) | (29 << 8))
            ->SetCorners(CORNER_RIGHT)
            ->SetSize(22, -1)
            ;
    topPanel->Insert(helpBtn);

    auto exitBtn = builder.Create<Gui::Button>()
            ->SetIcon((2) | (15 << 8))
            ->SetCorners(CORNER_LEFT)
            ->SetSize(22, -1)
            ;
    topPanel->Insert(exitBtn);
}

bool GameState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                _app.PopState();
                return true;
        }
    }

    return State::HandleEvent(event);
}
