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

#ifndef GUI_CHECKBOX_HPP
#define GUI_CHECKBOX_HPP

#include <functional>
#include <string>

#include <Gui/Widget.hpp>

namespace Gui {
    struct CheckBox : public TWidget<CheckBox> {
        virtual CheckBox* Connect(bool* value) = 0;
        virtual CheckBox* SetLabel(const std::string& label) = 0;
        virtual CheckBox* SetValue(bool value) = 0;
        virtual bool GetValue() = 0;
        virtual CheckBox* OnChanged(std::function<void(bool)> onChanged) = 0;
    };
}

#endif /* !GUI_CHECKBOX_HPP */
