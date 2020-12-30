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
#include <OpenGL/Gui/Button.hpp>
#include <OpenGL/Gui/Label.hpp>
#include <OpenGL/Gui/Panel.hpp>
#include <OpenGL/Gui/Radio.hpp>
#include <OpenGL/Gui/Text.hpp>

#include "oui.h"

using namespace OpenGL;
using namespace Blendish;

Panel::Panel(int i) : OpenGLWidget(i) {

}

Gui::Panel* Panel::Insert(Gui::WidgetBase* wdg) {
    uiInsert(_id, wdg->GetId());

    return this;
}

void Panel::Draw(NVG::NVGcontext* context) const {
    UIrect rect = uiGetRect(_id);

    bndBackground(context, rect.x, rect.y, rect.w, rect.h);
    bndBevelInset(context, rect.x, rect.y, rect.w, rect.h, 4, 4);

    OpenGLWidget::Draw(context);
}

