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

#include <OpenGL/Gui/Window.hpp>
#include <Blendish/Blendish.hpp>

using namespace OpenGL;
using namespace Blendish;

Window::Window(int i) : OpenGLWidget(i) {
    iconId = -1;
    uiSetEvents(item, UI_BUTTON0_DOWN | UI_BUTTON0_CAPTURE |
            UI_BUTTON0_HOT_UP);
}

Gui::Window* Window::SetTitle(const std::string& title) {
    this->title = title;

    return this;
}

Gui::Window* Window::SetBox(unsigned int boxType) {
    uiSetBox(item, boxType);

    return this;
}

Gui::Window* Window::SetIcon(int iconId) {
    this->iconId = iconId;

    return this;
}

Gui::Window* Window::SetSize(int w, int h) {
    uiSetSize(item, w, h);

    return this;
}

void Window::Draw(NVG::NVGcontext* context) const {
    BNDwidgetState state = (BNDwidgetState) uiGetState(item);
    UIrect rect = uiGetRect(this->item);

    bndNodeBackground(context, rect.x, rect.y, rect.w, rect.h,
            state, iconId, title.c_str(),
            nvgRGBf(0.392f, 0.392f, 0.392f));
}

bool isHeader(int item) {
    UIvec2 cursor = uiGetCursor();
    UIrect rect = uiGetRect(item);

    return cursor.y >= rect.y && cursor.y <= rect.y + BND_WIDGET_HEIGHT;
}

void Window::HandleEvent(UIevent event) {
    static UIrect startPos;

    switch (event) {
        case UI_BUTTON0_DOWN:
            if (isHeader(item))
                startPos = uiGetRect(item);
            break;
        case UI_BUTTON0_CAPTURE:
        {
            UIvec2 start = uiGetCursorStartDelta();
            int x = startPos.x + start.x;
            int y = startPos.y + start.y;

            uiSetMargins(item, x, y, 0, 0);
        }
            break;
        case UI_BUTTON0_HOT_UP:
            break;
        default:
            break;
    }
}
