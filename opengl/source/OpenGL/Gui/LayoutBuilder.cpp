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

#include <OpenGL/Gui/LayoutBuilder.hpp>
#include <OpenGL/Gui/Widget.hpp>
#include <OpenGL/Gui/Panel.hpp>

#include "oui.h"

using namespace OpenGL;

std::map<size_t, std::function<void*(void) >> LayoutBuilder::_registredWidgets;

LayoutBuilder::LayoutBuilder() {
    uiBeginLayout();
}

LayoutBuilder::~LayoutBuilder() {
    uiEndLayout();
}

Gui::Widget* LayoutBuilder::create(Gui::Type<Gui::Widget> type) {
    return createUi<OpenGL::Widget>();
}

Gui::Panel* LayoutBuilder::create(Gui::Type<Gui::Panel> type) {
    return static_cast<Gui::Panel*>(createUi<OpenGL::Panel>());
}

void LayoutBuilder::insert(size_t hash_code, void* widget) {
    
}


