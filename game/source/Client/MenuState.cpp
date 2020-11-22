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

#include <Client/ConnectState.hpp>
#include <Client/MenuState.hpp>
#include <Client/SettingState.hpp>
#include <Client/TestState.hpp>
#include <Gui/Button.hpp>
#include <Gui/Panel.hpp>
#include <Server/Engine.hpp>

using namespace Client;

MenuState::MenuState(Application* app) : State(app, "Menu state") {

}

void MenuState::onStartServer() {
    if (Server::Engine::Get().Start()) {
        auto f = std::bind(&MenuState::onStopServer, this);

        startServerBtn->SetLabel("Stop server");
        startServerBtn->OnClick(f);
    }
}

void MenuState::onStopServer() {
    if (Server::Engine::Get().Stop()) {
        auto f = std::bind(&MenuState::onStartServer, this);

        startServerBtn->SetLabel("Start server");
        startServerBtn->OnClick(f);
    }
}

void MenuState::BuildUI(Gui::LayoutBuilder& builder) {
    auto panel = builder.Create<Gui::Panel>();

    panel->SetLayout(LAYOUT_CENTER);
    panel->SetBox(BOX_COLUMN);
    panel->SetMargins(0, 0, 0, 0);
    panel->SetSize(200, 200);

    builder.Insert(panel);

    auto connectButton = builder.Create<Gui::Button>();

    connectButton->SetLabel("Connect");
    connectButton->OnClick([this]() {
        _app.PushState<ConnectState>(&_app);
    });
    connectButton->SetLayout(LAYOUT_HFILL | LAYOUT_TOP);
    connectButton->SetMargins(0, 1, 0, 0);

    panel->Insert(connectButton);

    startServerBtn = builder.Create<Gui::Button>();

    if (!Server::Engine::Get().Started()) {
        auto f = std::bind(&MenuState::onStartServer, this);

        startServerBtn->SetLabel("Start server");
        startServerBtn->OnClick(f);
    } else {
        auto f = std::bind(&MenuState::onStartServer, this);

        startServerBtn->SetLabel("Stop server");
        startServerBtn->OnClick(f);
    }

    startServerBtn->SetLayout(LAYOUT_HFILL | LAYOUT_TOP);
    startServerBtn->SetMargins(0, 1, 0, 0);

    panel->Insert(startServerBtn);

    auto testButton = builder.Create<Gui::Button>();

    testButton->SetLabel("TEST");
    testButton->OnClick([this]() {
        _app.PushState<TestState>(&_app);
    });
    testButton->SetLayout(LAYOUT_HFILL | LAYOUT_TOP);
    testButton->SetMargins(0, 1, 0, 0);

    panel->Insert(testButton);

    auto settingButton = builder.Create<Gui::Button>();

    settingButton->SetLabel("Settings");
    settingButton->OnClick([this]() {
        _app.PushState<SettingState>(&_app);
    });
    settingButton->SetLayout(LAYOUT_HFILL | LAYOUT_TOP);
    settingButton->SetMargins(0, 1, 0, 0);

    panel->Insert(settingButton);

    auto exitButton = builder.Create<Gui::Button>();

    exitButton->SetLabel("EXIT");
    exitButton->OnClick([this]() {
        _app.PopState();
    });
    exitButton->SetLayout(LAYOUT_HFILL | LAYOUT_TOP);
    exitButton->SetMargins(0, 1, 0, 0);

    panel->Insert(exitButton);
}

bool MenuState::HandleEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            _app.PopState();
            return true;
    }
    
    return State::HandleEvent(event);
}
