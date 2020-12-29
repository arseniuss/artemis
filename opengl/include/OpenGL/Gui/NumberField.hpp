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
    public:

        NumberField(int i);
        
        Gui::NumberField* SetLayout(unsigned int layoutType) override;
        Gui::NumberField* SetMargins(int a, int b, int c, int d) override;
        Gui::NumberField* SetSize(int w, int h) override;

        
        Gui::NumberField* SetLabel(const std::string& label) override;
        Gui::NumberField* SetValue(const std::string& value) override;
        
        void Draw(NVG::NVGcontext* context) const;
    };
}

#endif /* !OPENGL_GUI_NUMBERFIELD_HPP */
