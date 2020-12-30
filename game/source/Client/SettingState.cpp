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
    SDL_DisplayMode current;

    SDL_GetCurrentDisplayMode(0, &current);

    for (int i = 0; i < SDL_GetNumDisplayModes(0); i++) {
        SDL_DisplayMode mode;

        if (SDL_GetDisplayMode(0, i, &mode) == 0) {
            Common::Debug() << "Display mode #" << (i + 1) << " " <<
                    mode.w << "x" << mode.h << "@" << mode.refresh_rate <<
                    std::endl;

            size_t idx = _displayModes.size();

            _displayModes.push_back(mode);
            if (mode.w == current.w && mode.h == current.h &&
                    mode.refresh_rate == current.refresh_rate) {
                _currentDisplayMode = idx;
            }
        }
    }
}

void SettingState::BuildUI(Gui::LayoutBuilder& builder) {
    auto panel = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_CENTER)
            ->SetBox(BOX_COLUMN)
            ->SetMargins(0, 0, 0, 0)
            ->SetSize(700, 500);

    auto menuRow = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetBox(BOX_ROW);

    panel->Insert(menuRow);

    auto content = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_FILL)
            ->SetBox(BOX_LAYOUT);

    panel->Insert(content);

    auto buttonPanel = builder.Create<Gui::Panel>()
            ->SetSize(200, -1)
            ->SetLayout(LAYOUT_RIGHT)
            ->SetBox(BOX_ROW);

    auto applyBtn = builder.Create<Gui::Button>()
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetLabel("Apply");

    auto exitBtn = builder.Create<Gui::Button>()
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetLabel("Exit")
            ->OnClick([this]() {
                //TODO: confirm 
                _app.PopState();
            });

    buttonPanel->Insert(applyBtn);
    buttonPanel->Insert(exitBtn);

    panel->Insert(buttonPanel);

    auto graphButton = builder.Create<Gui::Radio>()
            ->Connect(&_selectedMenu)
            ->SetLabel("Graphics")
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetMargins(1, 1, 1, 1);

    graphButton->OnSelected([this](Gui::Radio * r) {
        _selectedMenu = r->GetId();
        this->RebuildUI();
    });

    auto audioButton = builder.Create<Gui::Radio>()
            ->Connect(&_selectedMenu)
            ->SetLabel("Audio")
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetMargins(1, 1, 1, 1);

    audioButton->OnSelected([this](Gui::Radio * r) {
        _selectedMenu = r->GetId();
        this->RebuildUI();
    });

    auto mouseButton = builder.Create<Gui::Radio>()
            ->Connect(&_selectedMenu)
            ->SetLabel("Mouse")
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetMargins(1, 1, 1, 1);

    mouseButton->OnSelected([this](Gui::Radio * r) {
        _selectedMenu = r->GetId();
        this->RebuildUI();
    });

    auto keyboardButton = builder.Create<Gui::Radio>()
            ->Connect(&_selectedMenu)
            ->SetLabel("Keyboard")
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetMargins(1, 1, 1, 1);

    keyboardButton->OnSelected([this](Gui::Radio * r) {
        _selectedMenu = r->GetId();
        this->RebuildUI();
    });

    menuRow->Insert(graphButton);
    menuRow->Insert(audioButton);
    menuRow->Insert(mouseButton);
    menuRow->Insert(keyboardButton);

    builder.Insert(panel);
    if (_selectedMenu == -1) {
        _selectedMenu = graphButton->GetId();
    }

    if (_selectedMenu == graphButton->GetId()) {
        BuildGraphicsContent(builder, content);
    }
}

bool SettingState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                _app.PopState();
                return true;
        }
    }

    return State::HandleEvent(event);
}

void SettingState::BuildGraphicsContent(Gui::LayoutBuilder& builder, Gui::Panel* content) {
    auto container = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_TOP | LAYOUT_LEFT)
            ->SetBox(BOX_COLUMN);

    content->Insert(container);

    auto row1 = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_LEFT | LAYOUT_TOP)
            ->SetBox(BOX_ROW);

    auto resLbl = builder.Create<Gui::Label>()
            ->SetSize(250, -1)
            ->SetLabel("Resolution:");
    auto resNi = builder.Create<Gui::NumberField>()
            ->SetSize(250, -1)
            ->SetLayout(LAYOUT_HFILL);

    if (_currentDisplayMode < _displayModes.size()) {
        auto& mode = _displayModes[_currentDisplayMode];

        resNi->SetValue(std::to_string(mode.w) + "x" + std::to_string(mode.h) +
                " " + std::to_string(mode.refresh_rate) + " Hz");
    }

    resNi->onIncClick([this]() {
        _currentDisplayMode++;
        _currentDisplayMode = _currentDisplayMode % _displayModes.size();
        RebuildUI();
    });

    resNi->OnDecrClick([this]() {
        _currentDisplayMode--;
        _currentDisplayMode = _currentDisplayMode % _displayModes.size();
        RebuildUI();
    });

    row1->Insert(resLbl);
    row1->Insert(resNi);

    container->Insert(row1);

    auto row2 = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_LEFT | LAYOUT_TOP)
            ->SetBox(BOX_ROW);
    auto fscrLbl = builder.Create<Gui::Label>()
            ->SetSize(250, -1)
            ->SetLabel("Fullscreen");
    auto fscrChb = builder.Create<Gui::CheckBox>();

    row2->Insert(fscrLbl);
    row2->Insert(fscrChb);

    container->Insert(row2);
}

