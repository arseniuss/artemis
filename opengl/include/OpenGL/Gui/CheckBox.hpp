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

#ifndef OPENGL_GUI_CHECKBOX_HPP
#define OPENGL_GUI_CHECKBOX_HPP

#include <Gui/CheckBox.hpp>
#include <OpenGL/Gui/Widget.hpp>

namespace OpenGL {

    struct CheckBox : public OpenGLWidget, virtual Gui::CheckBox {
    private:
        bool _value;
        std::string _label;
        std::function<void(bool) > _onChange;
    public:
        CheckBox(int i);

        CheckBox* SetLabel(const std::string& label) override;
        CheckBox* SetValue(bool value) override;
        CheckBox* OnChanged(std::function<void(bool) > onChanged) override;

        void Draw(NVG::NVGcontext* context) const override;

        void HandleEvent(UIevent event) override;

    };
}


#endif /* !OPENGL_GUI_CHECKBOX_HPP */
