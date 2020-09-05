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
#include <OpenGL/Gui/Button.hpp>

#include "oui.h"

using namespace OpenGL;
using namespace Blendish;

Button::Button(int i) : OpenGLWidget(i) {
    iconId = -1;
    onClick = nullptr;

    uiSetSize(i, 0, BND_WIDGET_HEIGHT);
    uiSetEvents(i, UI_BUTTON0_HOT_UP);
}

void Button::SetLabel(const std::string& label) {
    this->label = label;
    
}

void Button::OnClick(std::function<void() > onClickFunction) {
    this->onClick = onClickFunction;
}

void Button::SetLayout(unsigned int layout) {
    uiSetLayout(this->item, layout);
}

void Button::SetMargins(int a, int b, int c, int d) {
    uiSetMargins(this->item, a, b, c, d);
}

void Button::Draw(NVG::NVGcontext* context) const {
    OpenGLWidget::Draw(context);

    UIrect rect = uiGetRect(this->item);
    BNDwidgetState state = (BNDwidgetState) uiGetState(this->item);

    bndToolButton(context, rect.x, rect.y, rect.w, rect.h, -1, state,
            iconId,
            this->label.c_str());
}

void Button::HandleEvent(UIevent event) {
    if(event == UI_BUTTON0_HOT_UP) {
        if(this->onClick)
            this->onClick();
    }
}

