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

#ifndef OPENGL_GUI_NUMBERFIELD_HPP
#define OPENGL_GUI_NUMBERFIELD_HPP

#include <string>

#include <Gui/NumberField.hpp>
#include <OpenGL/Gui/Widget.hpp>

namespace OpenGL {

    struct NumberField : public OpenGLWidget, virtual Gui::NumberField {
    private:
        std::string _label;
        std::string _value;
        std::function<void() > _onDescClick;
        std::function<void() > _onIncClick;
    public:
        NumberField(int i);

        Gui::NumberField* SetLabel(const std::string& label) override;
        Gui::NumberField* SetValue(const std::string& value) override;
        Gui::NumberField* OnDecrClick(std::function<void() > onDecrClick) override;
        Gui::NumberField* onIncClick(std::function<void() > onIncClick) override;

        void HandleEvent(UIevent event) override;

        void Draw(NVG::NVGcontext* context) const;
    };
}

#endif /* !OPENGL_GUI_NUMBERFIELD_HPP */
