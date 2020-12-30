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

#ifndef OPENGL_GUI_RADIO_HPP
#define OPENGL_GUI_RADIO_HPP

#include <Gui/Radio.hpp>
#include <OpenGL/Gui/Widget.hpp>

namespace OpenGL {

    struct Radio : public OpenGLWidget, virtual Gui::Radio {
    private:
        int *_selectedId;
        std::string _label;
        int _iconId;
        int _width;

        std::function<void(Gui::Radio*) > _onSelected;
    public:
        Radio(int i);

        Gui::Radio* Connect(int* selectedId) override;
        Gui::Radio* SetIcon(int iconId) override;
        Gui::Radio* SetLabel(const std::string& label) override;

        Gui::Radio* OnSelected(std::function<void(Gui::Radio*) > onSelectedFunction) override;

        void HandleEvent(UIevent event) override;

        void Draw(NVG::NVGcontext* context) const;
    };
}

#endif /* !OPENGL_GUI_RADIO_HPP */
