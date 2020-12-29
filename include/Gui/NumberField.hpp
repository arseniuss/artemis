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

#ifndef GUI_NUMBERFIELD_HPP
#define GUI_NUMBERFIELD_HPP

#include <Gui/Widget.hpp>

namespace Gui {

    struct NumberField : virtual Widget {

        virtual NumberField* SetLayout(unsigned int layout) = 0;
        virtual NumberField* SetMargins(int a, int b, int c, int d) = 0;
        virtual NumberField* SetSize(int w, int h) = 0;
        
        virtual NumberField* SetLabel(const std::string& label) = 0;
        virtual NumberField* SetValue(const std::string& value) = 0;
    };
}

#endif /* !GUI_NUMBERFIELD_HPP */