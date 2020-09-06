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

    struct Button : OpenGLWidget, Gui::Button {
        std::string label;
        int iconId;
        std::function<void()> onClick;
        
        Button(int i);

        Gui::Button* SetLabel(const std::string& label) override;
        Gui::Button* OnClick(std::function<void() > onClickFunction) override;
        Gui::Button* SetLayout(unsigned int layout) override;
        Gui::Button* SetMargins(int a, int b, int c, int d) override;

        void Draw(NVG::NVGcontext* context) const override;

        void HandleEvent(UIevent event) override;

    };
}

#endif /* !OPENGL_GUI_BUTTON_HPP */
