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

#ifndef OPENGL_GUI_WIDGET_HPP
#define OPENGL_GUI_WIDGET_HPP

#include <Gui/Widget.hpp>
#include <NanoVG/NanoVG.hpp>

namespace OpenGL {

    struct OpenGLWidget {
        int item;

        OpenGLWidget(int i) : item(i) {
        }

        virtual void Draw(NVG::NVGcontext* context) const {
        }
    };

    struct Widget : OpenGLWidget, Gui::Widget {

        Widget(int i) : OpenGLWidget(i) {

        }
    };
}

#endif /* !OPENGL_GUI_WIDGET_HPP */

