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

#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include <functional>

#include <Gui/Widget.hpp>

namespace Gui {

    struct Button : public TWidget<Button> {
        virtual Button* SetLabel(const std::string& label) = 0;
        virtual Button* SetIcon(int iconId) = 0;
        virtual Button* OnClick(std::function<void() > onClickFunction) = 0;
    };
}

#endif /* !GUI_BUTTON_HPP */

