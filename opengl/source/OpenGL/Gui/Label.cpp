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
#include <OpenGL/Gui/Label.hpp>

using namespace OpenGL;
using namespace Blendish;

Label::Label(int i) : OpenGLWidget(i) {
    iconId = -1;
    label = "";
}

Gui::Label* Label::SetLabel(const std::string& text) {
    label = text;
    
    return this;
}

Gui::Label* Label::SetLayout(unsigned int layoutType) {
    uiSetLayout(item, layoutType);

    return this;
}

Gui::Label* Label::SetBox(unsigned int boxType) {
    uiSetBox(item, boxType);

    return this;
}

Gui::Label* Label::SetMargins(int a, int b, int c, int d) {
    uiSetMargins(item, a, b, c, d);

    return this;
}

Gui::Label* Label::SetSize(int w, int h) {
    uiSetSize(item, w, h);

    return this;
}

void Label::Draw(NVG::NVGcontext* context) const {
    OpenGLWidget::Draw(context);

    UIrect rect = uiGetRect(item);

    bndLabel(context, rect.x, rect.y, rect.w, rect.h, iconId, label.c_str());
}
