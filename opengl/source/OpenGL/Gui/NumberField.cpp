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
#include <OpenGL/Gui/NumberField.hpp>

#include "oui.h"
#include "Common/Debug.hpp"

using namespace OpenGL;
using namespace Blendish;

NumberField::NumberField(int i) : OpenGLWidget(i) {
    _label = "";
    _onDescClick = nullptr;
    _onIncClick = nullptr;

    uiSetSize(i, BND_TOOL_WIDTH, BND_WIDGET_HEIGHT);
    uiSetEvents(i, UI_BUTTON0_HOT_UP | UI_BUTTON0_DOWN);
}

Gui::NumberField* NumberField::SetLabel(const std::string& label) {
    _label = label;

    return this;
}

Gui::NumberField* NumberField::SetValue(const std::string& value) {
    _value = value;

    return this;
}

Gui::NumberField* NumberField::OnDecrClick(std::function<void() > onDecrClick) {
    _onDescClick = onDecrClick;
    
    return this;
}

Gui::NumberField* NumberField::onIncClick(std::function<void() > onIncClick) {
    _onIncClick = onIncClick;
    
    return this;
}

void NumberField::HandleEvent(UIevent event) {
    if (event == UI_BUTTON0_HOT_UP) {
        UIrect rect = uiGetRect(_id);
        UIvec2 cursor = uiGetCursor();

        if (cursor.x >= rect.x && cursor.x <= rect.x + rect.w &&
                cursor.y >= rect.y && cursor.y <= rect.y + rect.h) {
            int hw = rect.w / 2;
            int dx = cursor.x - rect.x;
            
            if(dx < hw) {
                if(_onDescClick) _onDescClick();
            } else {
                if(_onIncClick) _onIncClick();
            }
        }
    }
}

void NumberField::Draw(NVG::NVGcontext* context) const {
    OpenGLWidget::Draw(context);

    UIrect rect = uiGetRect(_id);
    BNDwidgetState state = (BNDwidgetState) uiGetState(_id);

    bndNumberField(context, rect.x, rect.y, rect.w, rect.h, BND_CORNER_NONE,
            state, _label.c_str(), _value.c_str());
}
