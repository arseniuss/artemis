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
    _iconId = -1;
    _onClick = nullptr;

    uiSetEvents(i, UI_BUTTON0_HOT_UP);
}

Gui::Button* Button::SetLabel(const std::string& label) {
    _label = label;

    return this;
}

Button* Button::SetIcon(int iconId) {
    _iconId = iconId;
    
    return this;
}

Gui::Button* Button::OnClick(std::function<void() > onClickFunction) {
    _onClick = onClickFunction;

    return this;
}

void Button::Draw(NVG::NVGcontext* context) const {
    UIrect rect = uiGetRect(_id);
    BNDwidgetState state = (BNDwidgetState) uiGetState(_id);

    bndToolButton(context, rect.x, rect.y, rect.w, rect.h, _corners, state,
            _iconId,
            _label.c_str());
    OpenGLWidget::Draw(context);
}

void Button::HandleEvent(UIevent event) {
    if (event == UI_BUTTON0_HOT_UP) {
        if (_onClick)
            _onClick();
    }
}

