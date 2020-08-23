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

#include <cassert>

#include <NanoVG/NanoVG.hpp>
#include <Blendish/Blendish.hpp>
#include <OpenGL/Gui.hpp>
#include <Gui/Oui.hpp>

#include "../Gui/internal.hpp"

using namespace NVG;
using namespace Gui;
using namespace Blendish;

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
            case UIType::Label:
                assert(head);
                DrawTestRect(vg, rect);
                break;
            case UIType::Button:
            {
                const UIButtonData *data = (UIButtonData *) head;

                bndToolButton(vg, rect.x, rect.y, rect.w, rect.h,
                        corners, (BNDwidgetState) uiGetState(item),
                        data->iconId, data->label);
                break;
            }
            case UIType::Radio:
            {
                const UIRadioData *data = (UIRadioData *) head;
                BNDwidgetState state = (BNDwidgetState) uiGetState(item);

                if (data->value && *data->value == item)
                    state = BND_ACTIVE;
                bndRadioButton(vg, rect.x, rect.y, rect.w, rect.h,
                        corners, state,
                        data->iconId, data->label);
                break;
            }
            case UIType::Slider:
                DrawTestRect(vg, rect);
                break;
            case UIType::Column:
                DrawTestRect(vg, rect);
                break;
            case UIType::Row:
                DrawTestRect(vg, rect);
                break;
            case UIType::Check:
                DrawTestRect(vg, rect);
                break;
            case UIType::Panel:
                bndBackground(vg, rect.x, rect.y, rect.w, rect.h);
                bndBevel(vg, rect.x, rect.y, rect.w, rect.h);
                DrawUIItems(vg, item, corners);
                break;
            case UIType::Text:
                DrawTestRect(vg, rect);
                break;
            case UIType::Ignore:
                DrawTestRect(vg, rect);
                break;
            case UIType::Rect:
                DrawTestRect(vg, rect);
                break;
            case UIType::HBox:
                DrawTestRect(vg, rect);
                break;
            case UIType::VBox:
                DrawTestRect(vg, rect);
                break;
            case UIType::Window:
            {
                BNDwidgetState state = (BNDwidgetState) uiGetState(item);
                UIWindowData *data = (UIWindowData *) head;

                bndNodeBackground(vg, rect.x, rect.y, rect.w, rect.h, state,
                        data->iconId, data->title,
                        nvgRGBf(0.392f, 0.392f, 0.392f));
                break;
            }
            default:
                DrawTestRect(vg, rect);
                DrawUIItems(vg, item, corners);
                break;
        }
    } else {
        DrawTestRect(vg, rect);
        DrawUIItems(vg, item, corners);
    }

    if (uiGetState(item) == UI_FROZEN) {
        nvgGlobalAlpha(vg, 1.0);
    }
}
