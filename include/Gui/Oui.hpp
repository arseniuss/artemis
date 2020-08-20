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
        VBox
    } UIType;
    
    using UIHandlerFunc = std::function<void(int item, UIevent event)>;
    
    typedef struct {
        UIType type;
        UIHandlerFunc handler;
    } UIData;
    
    typedef int (*CreatePanelFunc)();
    typedef int (*CreateButtonFunc)(int iconId, const char *label, UIHandlerFunc handler);
    typedef int (*CreateRadioFunc)(int iconId, const char *label, int* value);
    
    extern CreatePanelFunc CreatePanel;
    extern CreateButtonFunc CreateButton;
    extern CreateRadioFunc CreateRadio;
    
    void Validate();
}

#endif /* !GUI_OUI_HPP */

