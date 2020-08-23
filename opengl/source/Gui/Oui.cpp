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

#include <Gui/Oui.hpp>
#include <Blendish/Blendish.hpp>

#include "internal.hpp"

using namespace Blendish;

namespace Gui {

    int Label(int iconId, const char * label) {
        int item = uiItem();
        UILabelData *data = (UILabelData *) uiAllocHandle(item, sizeof (UILabelData));

        uiSetSize(item, 0, BND_WIDGET_HEIGHT);

        data->head.type = UIType::Label;
        data->head.handler1 = nullptr;

        data->iconId = iconId;
        data->label = label;

        return item;
    }

    int Button(int iconId, const char *label, UIHandlerFunc handler) {
        int item = uiItem();
        UIButtonData *data = (UIButtonData *) uiAllocHandle(item, sizeof (UIButtonData));

        uiSetSize(item, 0, BND_WIDGET_HEIGHT);
        uiSetEvents(item, UI_BUTTON0_HOT_UP);

        data->head.type = UIType::Button;
        data->head.handler1 = handler;
        data->iconId = iconId;
        data->label = label;

        return item;
    }

    int Radio(int iconId, const char *label, int* value) {
        int item = uiItem();
        UIRadioData *data = (UIRadioData *) uiAllocHandle(item, sizeof (UIRadioData));

        uiSetSize(item, label ? 0 : BND_TOOL_WIDTH, BND_WIDGET_HEIGHT);
        uiSetEvents(item, UI_BUTTON0_DOWN);

        data->head.type = UIType::Radio;
        data->head.handler1 = nullptr;
        data->iconId = iconId;
        data->label = label;
        data->value = value;

        return item;
    }

    void SliderHandler(int item, UIevent event) {
        UISliderData *data = (UISliderData *) uiGetHandle(item);

        if (data && data->progress) {
            static float sliderStart = 0.0;

            switch (event) {
                case UI_BUTTON0_DOWN:
                    sliderStart = *data->progress;
                    break;
                case UI_BUTTON0_CAPTURE:
                {
                    UIvec2 pos = uiGetCursorStartDelta();
                    UIrect rc = uiGetRect(item);
                    float value = sliderStart = ((float) pos.x / (float) rc.w);

                    value = (value < 0) ? 0 : (value > 1) ? 1 : value;
                    *data->progress = value;
                    break;
                }
                default:
                    break;
            }
        }
    }

    int Slider(const char *label, float *progress) {
        int item = uiItem();
        UISliderData *data = (UISliderData *) uiAllocHandle(item, sizeof (UISliderData));

        uiSetSize(item, 0, BND_WIDGET_HEIGHT);
        uiSetEvents(item, UI_BUTTON0_DOWN | UI_BUTTON0_CAPTURE);

        data->head.type = UIType::Slider;
        data->head.handler1 = SliderHandler;
        data->label = label;
        data->progress = progress;

        return item;
    }

    int Column() {
        int item = uiItem();

        uiSetBox(item, UI_COLUMN);

        return item;
    }

    int Panel() {
        int item = uiItem();
        UIData *data = (UIData *) uiAllocHandle(item, sizeof (UIData));

        data->type = UIType::Panel;
        data->handler1 = nullptr;

        return item;
    }

    bool isHeader(int item) {
        UIvec2 cursor = uiGetCursor();
        UIrect rect = uiGetRect(item);

        return cursor.y >= rect.y && cursor.y <= rect.y + BND_WIDGET_HEIGHT;
    }

    void WindowHandler(int item, UIevent event) {
        UIWindowData *data = (UIWindowData *) uiGetHandle(item);

        if (data) {
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
    }

    int Window(int iconId, const char *title) {
        int item = uiItem();
        UIWindowData *data = (UIWindowData *) uiAllocHandle(item,
                sizeof (UIWindowData));

        uiSetEvents(item, UI_BUTTON0_DOWN | UI_BUTTON0_CAPTURE |
                UI_BUTTON0_HOT_UP);

        data->head.type = UIType::Window;
        data->head.handler2 = WindowHandler;
        data->iconId = iconId;
        data->title = title;

        return item;
    }

}
