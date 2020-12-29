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

#include <Blendish/Blendish.hpp>
#include <OpenGL/Gui/Radio.hpp>

#include "oui.h"

using namespace OpenGL;
using namespace Blendish;

Radio::Radio(int i) : OpenGLWidget(i) {
    _selectedId = nullptr;
    _label = "";
    _iconId = -1;
    _width = BND_TOOL_WIDTH;

    uiSetSize(i, BND_TOOL_WIDTH, BND_WIDGET_HEIGHT);
    uiSetEvents(i, UI_BUTTON0_DOWN);
}

Gui::Radio* Radio::Connect(int* selectedId) {
    if (selectedId != nullptr) {
        _selectedId = selectedId;
    }

    return this;
}

Gui::Radio* Radio::SetIcon(int iconId) {
    _iconId = iconId;

    return this;
}

Gui::Radio* Radio::SetLabel(const std::string& label) {
    _label = label;

    return this;
}

Gui::Radio* Radio::OnSelected(std::function<void(Gui::Radio*) > onSelectedFunction) {
    _onSelected = onSelectedFunction;

    return this;
}

void Radio::HandleEvent(UIevent event) {
    if (event == UI_BUTTON0_DOWN) {
        if (_selectedId)
            *_selectedId = _id;
        if (_onSelected)
            _onSelected(this);
    }
}

void Radio::Draw(NVG::NVGcontext* context) const {
    OpenGLWidget::Draw(context);

    UIrect rect = uiGetRect(_id);
    BNDwidgetState state = (BNDwidgetState) uiGetState(_id);

    if (_selectedId != nullptr && *_selectedId == _id)
        state = BND_ACTIVE;
    bndRadioButton(context, rect.x, rect.y, rect.w, rect.h, BND_CORNER_ALL,
            state, _iconId, _label.c_str());
}
