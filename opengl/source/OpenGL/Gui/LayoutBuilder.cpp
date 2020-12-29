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

#include <cxxabi.h>

#include <SDL2/SDL_video.h>

#include <OpenGL/Gui/Button.hpp>
#include <OpenGL/Gui/Label.hpp>
#include <OpenGL/Gui/LayoutBuilder.hpp>
#include <OpenGL/Gui/NumberField.hpp>
#include <OpenGL/Gui/Panel.hpp>
#include <OpenGL/Gui/Radio.hpp>
#include <OpenGL/Gui/Text.hpp>
#include <OpenGL/Gui/Widget.hpp>
#include <OpenGL/Gui/Window.hpp>

#include "oui.h"

using namespace OpenGL;

std::map<size_t, std::function<void*(void) >> LayoutBuilder::_registredWidgets;

LayoutBuilder::LayoutBuilder(SDL_Window* window, bool dynamic) : _dynamic(dynamic) {
    if (!_dynamic) {
        int w, h;

        SDL_GetWindowSize(window, &w, &h);

        uiBeginLayout();

        int root = uiItem();

        uiSetSize(root, w, h);
        uiSetBox(root, UI_COLUMN);
    }
}

LayoutBuilder::~LayoutBuilder() {
    if (!_dynamic) {
        uiEndLayout();
    }
}

Gui::Widget* LayoutBuilder::create(Gui::Type<Gui::Widget> type) {
    return createUi<OpenGL::Widget>();
}

Gui::Panel* LayoutBuilder::create(Gui::Type<Gui::Panel> type) {
    return static_cast<Gui::Panel*> (createUi<OpenGL::Panel>());
}

Gui::Button* LayoutBuilder::create(Gui::Type<Gui::Button> type) {
    return static_cast<Gui::Button*> (createUi<OpenGL::Button>());
}

Gui::NumberField* LayoutBuilder::create(Gui::Type<Gui::NumberField> type) {
    return static_cast<Gui::NumberField*> (createUi<OpenGL::NumberField>());
}

Gui::Window* LayoutBuilder::create(Gui::Type<Gui::Window> type) {
    return static_cast<Gui::Window*> (createUi<OpenGL::Window>());
}

Gui::TextInput* LayoutBuilder::create(Gui::Type<Gui::TextInput> type) {
    return static_cast<Gui::TextInput*> (createUi<OpenGL::TextInput>());
}

Gui::Label* LayoutBuilder::create(Gui::Type<Gui::Label> type) {
    return static_cast<Gui::Label*> (createUi<OpenGL::Label>());
}

Gui::Radio* LayoutBuilder::create(Gui::Type<Gui::Radio> type) {
    return static_cast<Gui::Radio*> (createUi<OpenGL::Radio>());
}

void LayoutBuilder::insert(Gui::Widget* w) {
    uiInsert(0, w->GetId());
}
