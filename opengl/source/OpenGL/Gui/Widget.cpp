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
#include <OpenGL/Context.hpp>
#include <OpenGL/Gui/Widget.hpp>

#include "oui.h"

using namespace Blendish;
using namespace OpenGL;

OpenGLWidget::OpenGLWidget(int i) : _id(i) {
    _corners = CORNER_NONE;
    _isVisible = true;
    _debug = false;

    uiSetSize(_id, BND_TOOL_WIDTH, BND_WIDGET_HEIGHT);
    uiSetLayout(_id, 0);
    uiSetBox(_id, 0);
}

void OpenGLWidget::setBox(unsigned int box) {
    uiSetBox(_id, box);
}

void OpenGLWidget::setCorners(int corners) {
    _corners = corners;
}

void OpenGLWidget::setLayout(unsigned int layout) {
    uiSetLayout(_id, layout);
}

void OpenGLWidget::setMargins(int l, int t, int r, int b) {
    uiSetMargins(_id, l, t, r, b);
}

void OpenGLWidget::setSize(int w, int h) {
    if (w < 0) w = BND_TOOL_WIDTH;
    if (h < 0) h = BND_WIDGET_HEIGHT;

    uiSetSize(_id, w, h);
}

void OpenGLWidget::setIsVisible(bool isVisible) {
    _isVisible = isVisible;
}

void OpenGLWidget::setDebug(bool debug) {
    _debug = debug;
}

int OpenGLWidget::GetId() const {
    return _id;
}

void OpenGLWidget::Draw(NVG::NVGcontext* context) const {
    if (Context::Debug || _debug) {
        UIrect rect = uiGetRect(_id);

        int v = 2;

        rect.x += v;
        rect.y += v;
        rect.w -= v * 2;
        rect.h -= v * 2;

        nvgBeginPath(context);
        nvgMoveTo(context, rect.x, rect.y);
        nvgLineTo(context, rect.x + rect.w, rect.y);
        nvgLineTo(context, rect.x + rect.w, rect.y + rect.h);
        nvgLineTo(context, rect.x, rect.y + rect.h);
        nvgLineTo(context, rect.x, rect.y);
        nvgStrokeColor(context, nvgRGB(255, 0, 0));
        nvgStroke(context);
    }
}

void OpenGLWidget::HandleEvent(UIevent event) {
}

Widget::Widget(int i) : OpenGLWidget(i) {
}



