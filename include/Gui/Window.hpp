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

#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include <string>

#include <Gui/Widget.hpp>

namespace Gui {

    struct Window : public Widget {
        Window(int i) : Widget(i) {
            
        }
        
        virtual Window* SetTitle(const std::string& title) = 0;
        virtual Window* SetIcon(int iconId) = 0;
        virtual Window* SetSize(int w, int h) = 0;
        virtual Window* SetBox(unsigned int boxType) = 0;
    };
}


#endif /* !GUI_WINDOW_HPP */
