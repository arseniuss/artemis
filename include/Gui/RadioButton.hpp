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

#ifndef GUI_RADIO_HPP
#define GUI_RADIO_HPP

#include <functional>
#include <string>

#include <Gui/Widget.hpp>

namespace Gui {

    struct RadioButton : public TWidget<RadioButton> {

        
        virtual RadioButton* Connect(int* selectedId) = 0;
        virtual RadioButton* SetIcon(int iconId) = 0;
        virtual RadioButton* SetLabel(const std::string& label) = 0;
       
        
        virtual RadioButton* OnSelected(std::function<void(Gui::RadioButton*) > onClickFunction) = 0;
    };
}


#endif /* !GUI_RADIO_HPP */
