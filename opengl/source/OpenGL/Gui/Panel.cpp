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

#include <OpenGL/Gui/Panel.hpp>
#include <Blendish/Blendish.hpp>
#include <OpenGL/Gui/Button.hpp>

#include "oui.h"

using namespace OpenGL;
using namespace Blendish;

void Panel::SetLayout(unsigned int layoutType) {
    uiSetLayout(item, layoutType);
}

void Panel::SetMargins(int a, int b, int c, int d) {
    uiSetMargins(item, a, b, c, d);
}

void Panel::SetSize(int w, int h) {
    uiSetSize(item, w, h);
}

void Panel::Insert(Gui::Button* btn) {
    OpenGL::Button* w = static_cast<OpenGL::Button*>(btn);
    
    uiInsert(item, w->item);
}

void Panel::SetBox(unsigned int boxType) {
    uiSetBox(item, boxType);
}

void Panel::Draw(NVG::NVGcontext* context) const {
    OpenGLWidget::Draw(context);
    
    UIrect rect = uiGetRect(item);

    bndBackground(context, rect.x, rect.y, rect.w, rect.h);
    bndBevel(context, rect.x, rect.y, rect.w, rect.h);
}

