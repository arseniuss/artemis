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

#include <Gui/Common.hpp>

#include "Client/SettingState.hpp"

using namespace Client;

void SettingState::ApplyAndSave() {
    auto* window = _app.GetGraphics()->GetWindow();
    auto& current = _displayModes[_currentDisplayMode];

    _app.GetConfig()->Set("Graphics", "Fullscreen", _fullscreen);
    _app.GetConfig()->Set("Graphics", "ScreenWidth", current.w);
    _app.GetConfig()->Set("Graphics", "ScreenHeight", current.h);
    _app.GetConfig()->Set("Graphics", "ScreenFreqency", current.refresh_rate);

    if (_fullscreen) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    } else {
        SDL_SetWindowFullscreen(window, 0);
    }

    SDL_SetWindowSize(window, current.w, current.h);

    _app.GetConfig()->Save();
    RebuildUI();
}

SettingState::SettingState(Application* app) : State(app, "Setting state") {
    SDL_DisplayMode current;
    SDL_Window* window = app->GetContext().GetWindow();

    int idx = SDL_GetWindowDisplayIndex(window);

    _fullscreen = app->GetConfig()->Get("Graphics", "Fullscreen", false);

    SDL_GetCurrentDisplayMode(idx, &current);

    for (int i = 0; i < SDL_GetNumDisplayModes(0); i++) {
        SDL_DisplayMode mode;

        if (SDL_GetDisplayMode(idx, i, &mode) == 0) {
            Common::Debug() << "Display #" << idx << " mode #" << (i + 1) << " " <<
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
    auto size = _app.GetContext().GetSize();

    auto panel = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_CENTER)
            ->SetBox(BOX_COLUMN)
            ->SetMargins(0, 0, 0, 0)
            ->SetSize(0.8 * size.x, 0.7 * size.y);

    auto menuRow = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetBox(BOX_ROW);

    panel->Insert(menuRow);

    auto content = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_FILL)
            ->SetMargins(10, 10, 10, 10)
            ->SetBox(BOX_LAYOUT);

    panel->Insert(content);

    auto buttonPanel = builder.Create<Gui::Panel>()
            ->SetSize(200, -1)
            ->SetLayout(LAYOUT_HFILL | LAYOUT_RIGHT)
            ->SetBox(BOX_ROW);

    auto applyBtn = builder.Create<Gui::Button>()
            ->SetLayout(LAYOUT_RIGHT)
            ->SetSize(200, -1)
            ->SetLabel("Apply & Save")
            ->OnClick(std::bind(&SettingState::ApplyAndSave, this));

    auto exitBtn = builder.Create<Gui::Button>()
            ->SetLayout(LAYOUT_RIGHT)
            ->SetSize(200, -1)
            ->SetLabel("Exit")
            ->OnClick([this]() {
                //TODO: confirm 
                _app.PopState();
            });

    buttonPanel->Insert(applyBtn);
    buttonPanel->Insert(exitBtn);

    panel->Insert(buttonPanel);

    auto graphButton = builder.Create<Gui::RadioButton>()
            ->Connect(&_selectedMenu)
            ->SetLabel("Graphics")
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetMargins(1, 1, 1, 1);

    graphButton->OnSelected([this](Gui::RadioButton * r) {
        _selectedMenu = r->GetId();
        this->RebuildUI();
    });

    auto audioButton = builder.Create<Gui::RadioButton>()
            ->Connect(&_selectedMenu)
            ->SetLabel("Audio")
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetMargins(1, 1, 1, 1);

    audioButton->OnSelected([this](Gui::RadioButton * r) {
        _selectedMenu = r->GetId();
        this->RebuildUI();
    });

    auto mouseButton = builder.Create<Gui::RadioButton>()
            ->Connect(&_selectedMenu)
            ->SetLabel("Mouse")
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetMargins(1, 1, 1, 1);

    mouseButton->OnSelected([this](Gui::RadioButton * r) {
        _selectedMenu = r->GetId();
        this->RebuildUI();
    });

    auto keyboardButton = builder.Create<Gui::RadioButton>()
            ->Connect(&_selectedMenu)
            ->SetLabel("Keyboard")
            ->SetLayout(LAYOUT_HFILL | LAYOUT_TOP)
            ->SetMargins(1, 1, 1, 1);

    keyboardButton->OnSelected([this](Gui::RadioButton * r) {
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
            ->SetLayout(LAYOUT_FILL)
            ->SetBox(BOX_COLUMN)
            ->SetIsVisible(true)
            ;

    content->Insert(container);

    auto row1 = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_LEFT | LAYOUT_HFILL)
            ->SetBox(BOX_ROW)
            ->SetIsVisible(false)
            ;
    auto resLbl = builder.Create<Gui::Label>()
            ->SetSize(250, -1)
            ->SetLabel("Resolution:")
            ;
    auto resNi = builder.Create<Gui::NumberField>()
            ->SetSize(250, -1)
            ;
    auto row1Wrap = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_HFILL)
            ->SetIsVisible(false)
            ;

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
    row1->Insert(row1Wrap);

    container->Insert(row1);

    auto row2 = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_LEFT | LAYOUT_HFILL)
            ->SetBox(BOX_ROW)
            ->SetIsVisible(false)
            ;
    auto fscrLbl = builder.Create<Gui::Label>()
            ->SetSize(250, -1)
            ->SetLabel("Fullscreen");
    auto fscrChb = builder.Create<Gui::CheckBox>()
            ->Connect(&_fullscreen);
    auto row2Wrap = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_HFILL)
            ->SetIsVisible(false)
            ;
    row2->Insert(fscrLbl);
    row2->Insert(fscrChb);
    row2->Insert(row2Wrap);

    container->Insert(row2);

    auto containerWrap = builder.Create<Gui::Panel>()
            ->SetLayout(LAYOUT_FILL)
            ->SetIsVisible(false)
            ;

    container->Insert(containerWrap);
}

