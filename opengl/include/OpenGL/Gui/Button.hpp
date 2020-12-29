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

#ifndef OPENGL_GUI_BUTTON_HPP
#define OPENGL_GUI_BUTTON_HPP

#include <Gui/Button.hpp>
#include <OpenGL/Gui/Widget.hpp>

namespace OpenGL {

    struct Button : public OpenGLWidget, virtual Gui::Button {
        std::string _label;
        int _iconId;
        std::function<void()> _onClick;
        
        Button(int i);
                
        // Gui::Button

        Gui::Button* SetLabel(const std::string& label) override;
        Gui::Button* OnClick(std::function<void() > onClickFunction) override;

        void Draw(NVG::NVGcontext* context) const override;

        void HandleEvent(UIevent event) override;

    };
}

#endif /* !OPENGL_GUI_BUTTON_HPP */

