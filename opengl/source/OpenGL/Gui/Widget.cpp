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

#include <OpenGL/Gui/Widget.hpp>
#include <Blendish/Blendish.hpp>    

#include "oui.h"

using namespace Blendish;
using namespace OpenGL;

OpenGLWidget::OpenGLWidget(int i) : _id(i) {
}

void OpenGLWidget::setBox(unsigned int box) {
    uiSetBox(_id, box);
}

void OpenGLWidget::setLayout(unsigned int layout) {
    uiSetLayout(_id, layout);
}

void OpenGLWidget::setMargins(int a, int b, int c, int d) {
    uiSetMargins(_id, a, b, c, d);
}

void OpenGLWidget::setSize(int w, int h) {
    if (w < 0) w = BND_TOOL_WIDTH;
    if (h < 0) h = BND_WIDGET_HEIGHT;
    
    uiSetSize(_id, w, h);
}

int OpenGLWidget::GetId() const {
    return _id;
}

void OpenGLWidget::Draw(NVG::NVGcontext* context) const {

}

void OpenGLWidget::HandleEvent(UIevent event) {
}

Widget::Widget(int i) : OpenGLWidget(i) {
}



