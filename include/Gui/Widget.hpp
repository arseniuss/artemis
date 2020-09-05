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

#ifndef GUI_WIDGET_HPP
#define GUI_WIDGET_HPP

namespace Gui {
    
#define LAYOUT_LEFT     0x020
#define LAYOUT_TOP      0x040
#define LAYOUT_RIGHT    0x080
#define LAYOUT_DOWN     0x100
#define LAYOUT_HFILL    0x0a0
#define LAYOUT_VFILL    0x140
#define LAYOUT_HCENTER  0x000
#define LAYOUT_VCENTER  0x000
#define LAYOUT_CENTER   0x000
#define LAYOUT_FILL     0x1e0
#define LAYOUT_BREAK    0x200
    
#define BOX_ROW         0x002
#define BOX_COLUMN      0x003
#define BOX_LAYOUT      0x000
#define BOX_FLEX        0x002
#define BOX_NO_WRAP     0x000
#define BOX_WRAP        0x004
#define BOX_START       

    struct Widget {

    };
}

#endif /* !GUI_WIDGET_HPP */
