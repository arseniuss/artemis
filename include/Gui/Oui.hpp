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

#ifndef GUI_OUI_HPP
#define GUI_OUI_HPP

#include <oui.h>
#include <functional>

namespace Gui {

    typedef enum class UIType {
        Label,
        Button,
        Radio,
        Slider,
        Column,
        Row,
        Check,
        Panel,
        Text,
        Ignore,
        Rect,
        HBox,
        VBox,
        Window
    } UIType;

    using UIHandlerFunc = std::function<void(int item, UIevent event)>;

    typedef struct {
        UIType type;
        UIHandlerFunc handler1;
        void (*handler2)(int item, UIevent event);
    } UIData;

    typedef int (*CreateLabelFunc)(int iconId, const char *label);
    typedef int (*CreateButtonFunc)(int iconId, const char *label, UIHandlerFunc handler);
    typedef int (*CreateRadioFunc)(int iconId, const char *label, int* value);
    typedef int (*CreateSliderFunc)(const char *label, float *progress);
    typedef int (*CreateColumnFunc)();
    typedef int (*CreatePanelFunc)();
    typedef int (*CreateWindowFunc)(int iconId, const char *title);

    extern CreateLabelFunc CreateLabel;
    extern CreateButtonFunc CreateButton;
    extern CreateRadioFunc CreateRadio;
    extern CreateSliderFunc CreateSlider;
    extern CreateColumnFunc CreateColumn;
    extern CreatePanelFunc CreatePanel;
    extern CreateWindowFunc CreateWindow;

    void Validate();
}

#endif /* !GUI_OUI_HPP */

