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

using namespace OpenGL;
using namespace Blendish;

NumberField::NumberField(int i) : OpenGLWidget(i) {
    _label = "";

    uiSetSize(i, BND_TOOL_WIDTH, BND_WIDGET_HEIGHT);
}

Gui::NumberField* NumberField::SetLayout(unsigned int layoutType) {
    uiSetLayout(_id, layoutType);

    return this;
}

Gui::NumberField* NumberField::SetMargins(int a, int b, int c, int d) {
    uiSetMargins(_id, a, b, c, d);

    return this;
}

Gui::NumberField* NumberField::SetSize(int w, int h) {
    if (w < 0) w = BND_TOOL_WIDTH;
    if (h < 0) h = BND_WIDGET_HEIGHT;

    uiSetSize(_id, w, h);
    
    return this;
}

Gui::NumberField* NumberField::SetLabel(const std::string& label) {
    _label = label;

    return this;
}

Gui::NumberField* NumberField::SetValue(const std::string& value) {
    _value = value;

    return this;
}

void NumberField::Draw(NVG::NVGcontext* context) const {
    OpenGLWidget::Draw(context);

    UIrect rect = uiGetRect(_id);
    BNDwidgetState state = (BNDwidgetState) uiGetState(_id);

    bndNumberField(context, rect.x, rect.y, rect.w, rect.h, BND_CORNER_NONE,
            state, _label.c_str(), _value.c_str());
}

