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

#ifndef GUI_TEXTINPUT_HPP
#define GUI_TEXTINPUT_HPP

#include <string>

#include <Gui/Widget.hpp>

namespace Gui {

    struct TextInput : virtual Widget {


        virtual TextInput* SetText(const std::string& text) = 0;
        virtual const std::string& GetText() const = 0;
        virtual TextInput* SetLayout(unsigned int layout) = 0;
        virtual TextInput* SetMargins(int a, int b, int c, int d) = 0;
    };
}

#endif /* !GUI_TEXTINPUT_HPP */
