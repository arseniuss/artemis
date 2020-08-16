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
#include <OpenGL/Gui.hpp>
#include <Gui/Oui.hpp>
#include <oui.h>

using namespace NVG;

static void DrawTestRect(NVG::NVGcontext *vg, UIrect rect) {
#ifndef NDEBUG
    nvgBeginPath(vg);
    nvgRect(vg, rect.x + 0.5, rect.y + 0.5, rect.w - 1, rect.h - 1);
    nvgStrokeColor(vg, nvgRGBf(1, 0, 0));
    nvgStrokeWidth(vg, 1);
    nvgStroke(vg);
#endif
}

void DrawUIItems(NVG::NVGcontext *vg, int item, int corners) {
    int kid = uiFirstChild(item);
    while (kid > 0) {
        OpenGL::DrawUI(vg, kid, corners);
        kid = uiNextSibling(kid);
    }
}

void OpenGL::DrawUI(NVG::NVGcontext *vg, int item, int corners) {
    const Gui::UIData *head = (const Gui::UIData *)uiGetHandle(item);
    UIrect rect = uiGetRect(item);

    if (uiGetState(item) == UI_FROZEN) {
        nvgGlobalAlpha(vg, BND_DISABLED_ALPHA);
    }

    if (head) {
        switch (head->type) {
            default:
                DrawTestRect(vg, rect);
                DrawUIItems(vg, item, corners);
                break;
        }
    }
}
