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

    int Panel() {
        int item = uiItem();
        UIData *data = (UIData *) uiAllocHandle(item, sizeof (UIData));

        data->type = UIType::Panel;
        data->handler = nullptr;

        return item;
    }

    int Button(int iconId, const char *label, UIHandlerFunc handler) {
        int item = uiItem();
        UIButtonData *data = (UIButtonData *) uiAllocHandle(item, sizeof (UIButtonData));

        uiSetSize(item, 0, BND_WIDGET_HEIGHT);
        uiSetEvents(item, UI_BUTTON0_HOT_UP);

        data->head.type = UIType::Button;
        data->head.handler = handler;
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
        data->head.handler = nullptr;
        data->iconId = iconId;
        data->label = label;
        data->value = value;

        return item;
    }
}
