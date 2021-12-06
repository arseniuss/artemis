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

#include <memory>

#include <Gui/Widget.hpp>
#include <NanoVG/NanoVG.hpp>

#include "oui.h"

namespace OpenGL {

    struct OpenGLWidget : virtual Gui::Widget {
    protected:
        int _corners;
        bool _isVisible;
        bool _debug;

        void setBox(unsigned int box) override;
        void setCorners(int corners) override;
        void setLayout(unsigned int layout) override;
        void setMargins(int a, int b, int c, int d) override;
        void setSize(int w, int h) override;
        void setIsVisible(bool isVisible) override;
        void setDebug(bool debug) override;
    public:
        int _id;

        OpenGLWidget(int i);

        int GetId() const override;

        virtual void Draw(NVG::NVGcontext* context) const;

        virtual void HandleEvent(UIevent event);
    };

    struct Widget : public OpenGLWidget {
        Widget(int i);
    };
}

#endif /* !OPENGL_GUI_WIDGET_HPP */

