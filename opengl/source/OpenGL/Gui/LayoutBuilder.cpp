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

#include <memory>

#include <SDL2/SDL_video.h>

#include <Graphics/Context.hpp>
#include <OpenGL/Context.hpp>
#include <OpenGL/Gui/Button.hpp>
#include <OpenGL/Gui/CheckBox.hpp>
#include <OpenGL/Gui/Label.hpp>
#include <OpenGL/Gui/LayoutBuilder.hpp>
#include <OpenGL/Gui/NumberField.hpp>
#include <OpenGL/Gui/Panel.hpp>
#include <OpenGL/Gui/RadioButton.hpp>
#include <OpenGL/Gui/Text.hpp>
#include <OpenGL/Gui/Widget.hpp>
#include <OpenGL/Gui/Window.hpp>

#include "oui.h"

using namespace OpenGL;

LayoutBuilder::LayoutBuilder(std::shared_ptr<Context> context) :
_context(context) {
    int w, h;

    auto window = context->GetWindow();

    SDL_GetWindowSize(window, &w, &h);

    uiBeginLayout();

    int root = uiItem();

    uiSetSize(root, w, h);
    uiSetBox(root, UI_COLUMN);
}

LayoutBuilder::~LayoutBuilder() {
    uiEndLayout();
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

Gui::CheckBox* LayoutBuilder::create(Gui::Type<Gui::CheckBox> type) {
    return static_cast<Gui::CheckBox*> (createUi<OpenGL::CheckBox>());
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

Gui::RadioButton* LayoutBuilder::create(Gui::Type<Gui::RadioButton> type) {
    return static_cast<Gui::RadioButton*> (createUi<OpenGL::RadioButton>());
}

void LayoutBuilder::insert(Gui::WidgetBase* w) {
    uiInsert(0, w->GetId());
}
