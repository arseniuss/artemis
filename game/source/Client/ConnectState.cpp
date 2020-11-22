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
#include <Common/Debug.hpp>
#include <Network/Client.hpp>
#include <Network/Context.hpp>

using namespace Client;

ConnectState::ConnectState(Application* app) : State(app, "Connect state") {

}

void ConnectState::BuildUI(Gui::LayoutBuilder& builder) {
    auto panel = builder.Create<Gui::Panel>();

    panel->SetLayout(LAYOUT_CENTER);
    panel->SetBox(BOX_COLUMN);
    panel->SetMargins(0, 0, 0, 0);
    panel->SetSize(200, 200);

    builder.Insert(panel);

    _textInput = builder.Create<Gui::Text>();
    
    _textInput->SetText("127.0.0.1");
    _textInput->SetLayout(LAYOUT_HFILL);
    
    panel->Insert(_textInput);

    auto connectButton = builder.Create<Gui::Button>();

    connectButton->SetLabel("Connect");
    connectButton->SetLayout(LAYOUT_HFILL);
    connectButton->OnClick([this]() {
        Network::Context& net = _app.GetNetwork();

        Network::Client *client = net.Create<Network::Client>();

        client->Connect("localhost", Network::Context::DefaultPort);

        _app.AddLoop([this, client]() -> bool {
            auto status = client->GetConnectionStatus();

            switch (status) {
                case Network::Failed:
                    return false;
                case Network::Connected:
                    return false;
                case Network::Connecting:
                    return true;
            }
            
            return true; /* Continue */
        });
    });

    panel->Insert(connectButton);
}

bool ConnectState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                _app.PopState();
                return true;
        }
    }
    
    return State::HandleEvent(event);
}



