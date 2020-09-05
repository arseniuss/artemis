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

#ifndef GUI_PANEL_HPP
#define GUI_PANEL_HPP

#include <Gui/Widget.hpp>
#include <Gui/Button.hpp>

namespace Gui {
    struct Panel {        
        virtual void SetLayout(unsigned int layoutType) = 0;
        virtual void SetBox(unsigned int boxType) = 0;
        virtual void SetMargins(int a, int b, int c, int d) = 0;
        virtual void SetSize(int w, int h) = 0;
        
        virtual void Insert(Gui::Button* btn) = 0;
    };
}

#endif /* !GUI_PANEL_HPP */
