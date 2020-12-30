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

#ifndef OPENGL_GUI_LAYOUTBUILDER_HPP
#define OPENGL_GUI_LAYOUTBUILDER_HPP

#include <functional>
#include <map>

#include <Gui/LayoutBuilder.hpp>

#include "../../oui.h"

namespace OpenGL {

    class Context;

    class LayoutBuilder : public Gui::LayoutBuilder {
    protected:
        std::shared_ptr<Context> _context;

        Gui::Button* create(Gui::Type<Gui::Button> type) override;
        Gui::CheckBox* create(Gui::Type<Gui::CheckBox> type) override;
        Gui::Label* create(Gui::Type<Gui::Label> type) override;
        Gui::NumberField* create(Gui::Type<Gui::NumberField> type) override;
        Gui::Panel* create(Gui::Type<Gui::Panel> type) override;
        Gui::Radio* create(Gui::Type<Gui::Radio> type) override;
        Gui::TextInput* create(Gui::Type<Gui::TextInput> type) override;
        Gui::Widget* create(Gui::Type<Gui::Widget> type) override;
        Gui::Window* create(Gui::Type<Gui::Window> type) override;

        template<typename T>
        T* createUi() {
            int item = uiItem();
            void *data = uiAllocHandle(item, sizeof (T));

            T* t = new(data) T(item);

            return t;
        }

        void insert(Gui::WidgetBase*) override;
    public:
        LayoutBuilder(std::shared_ptr<Context> context);
        ~LayoutBuilder();
    };
}

#endif /* !OPENGL_GUI_LAYOUTBUILDER_HPP */
