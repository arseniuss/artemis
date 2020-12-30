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

#include <NanoVG/NanoVG.hpp>
#include <Blendish/Blendish.hpp>
#include <OpenGL/Gui/CheckBox.hpp>

#include "oui.h"

using namespace OpenGL;
using namespace Blendish;

CheckBox::CheckBox(int i) : OpenGLWidget(i) {
    _value = false;
    _label = "";
    _onChange = nullptr;

    uiSetSize(i, BND_TOOL_WIDTH, BND_WIDGET_HEIGHT);
    uiSetEvents(i, UI_BUTTON0_DOWN);
}

CheckBox* CheckBox::SetLabel(const std::string& label) {
    _label = label;

    return this;
}

CheckBox* CheckBox::SetValue(bool value) {
    _value = value;

    if (_onChange) _onChange(value);

    return this;
}

CheckBox* CheckBox::OnChanged(std::function<void(bool) > onChanged) {
    _onChange = onChanged;

    return this;
}

void CheckBox::Draw(NVG::NVGcontext* context) const {
    UIrect rect = uiGetRect(_id);
    BNDwidgetState state = (BNDwidgetState) uiGetState(_id);

    if (_value)
        state = BND_ACTIVE;

    bndOptionButton(context, rect.x, rect.y, rect.w, rect.h, state,
            _label.c_str());
    OpenGLWidget::Draw(context);
}

void CheckBox::HandleEvent(UIevent event) {
    if (event == UI_BUTTON0_DOWN) {
        _value = !_value;
    }
}
