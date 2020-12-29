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

#ifndef GUI_LABEL_HPP
#define GUI_LABEL_HPP

#include <string>

#include <Gui/Widget.hpp>

namespace Gui {

    struct Label : virtual Widget {

        virtual Label* SetLabel(const std::string& text) = 0;

        virtual Label* SetLayout(unsigned int layoutType) = 0;
        virtual Label* SetBox(unsigned int boxType) = 0;
        virtual Label* SetMargins(int a, int b, int c, int d) = 0;
        virtual Label* SetSize(int w, int h) = 0;
    };
}

#endif /* !GUI_LABEL_HPP */
