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

namespace Gui {
    typedef enum {
        Label,
    } UIType;
    
    typedef struct {
        UIType type;
        UIhandler handler;
    } UIData;
    
    static inline int Panel() {
        int item = uiItem();
        UIData *data = (UIData *)uiAllocHandle(item, sizeof(UIData));
        
        data->type = Label;
        data->handler = nullptr;
        
        return item;
    }
}

#endif /* !GUI_OUI_HPP */

