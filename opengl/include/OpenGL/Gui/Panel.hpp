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

#ifndef OPENGL_GUI_PANEL_HPP
#define OPENGL_GUI_PANEL_HPP

#include <Gui/Panel.hpp>
#include <OpenGL/Gui/Widget.hpp>

namespace OpenGL {

    struct Panel : OpenGLWidget, Gui::Panel {

        Panel(int i) : Gui::Panel(i) {

        }

        Gui::Panel* SetLayout(unsigned int layoutType) override;
        Gui::Panel* SetBox(unsigned int boxType) override;
        Gui::Panel* SetMargins(int a, int b, int c, int d) override;
        Gui::Panel* SetSize(int w, int h) override;
        Gui::Panel* Insert(Gui::Widget* wdg) override;

        void Draw(NVG::NVGcontext* context) const;

    };
}

#endif /* !OPENGL_GUI_PANEL_HPP */

