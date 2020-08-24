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

#include "oui.h"

using namespace OpenGL;
using namespace Blendish;

void Panel::SetLayout(Gui::LayoutType layoutType) {
    switch (layoutType) {
        case Gui::LayoutType::Center:
            uiSetLayout(item, UI_CENTER);
            break;
    }
}

void Panel::SetMargins(int a, int b, int c, int d) {
    uiSetMargins(item, a, b, c, d);
}

void Panel::SetSize(int w, int h) {
    uiSetSize(item, w, h);
}

void Panel::SetBox(Gui::BoxType boxType) {
    switch (boxType) {
        case Gui::BoxType::Column:
            uiSetBox(item, UI_COLUMN);
            break;
    }
}

void Panel::Draw(NVG::NVGcontext* context) const {
    UIrect rect = uiGetRect(item);

    bndBackground(context, rect.x, rect.y, rect.w, rect.h);
    bndBevel(context, rect.x, rect.y, rect.w, rect.h);
}

