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

#ifndef GUI_LAYOUTBUILDER_HPP
#define GUI_LAYOUTBUILDER_HPP

#include <cstddef>
#include <typeinfo>
#include <utility>

#include <Gui/Button.hpp>
#include <Gui/Label.hpp>
#include <Gui/Panel.hpp>
#include <Gui/Text.hpp>
#include <Gui/Widget.hpp>
#include <Gui/Window.hpp>

namespace Gui {

    template<typename T>
    struct Type {
        size_t hash;
    };

    class LayoutBuilder {
    protected:
        virtual Gui::Widget* create(Type<Gui::Widget> type) = 0;
        virtual Gui::Panel* create(Type<Gui::Panel> type) = 0;
        virtual Gui::Button* create(Type<Gui::Button> type) = 0;
        virtual Gui::Window* create(Type<Gui::Window> type) = 0;
        virtual Gui::Text* create(Type<Gui::Text> type) = 0;
        virtual Gui::Label* create(Type<Gui::Label> type) = 0;

        virtual void insert(Gui::Widget*) = 0;
        virtual void insert(Gui::Panel*) = 0;
        virtual void insert(Gui::Window*) = 0;
        virtual void insert(Gui::Label*) = 0;
    public:

        LayoutBuilder() {
        }

        template<typename T>
        T* Create() {
            Type<T> type;

            type.hash = typeid (T).hash_code();

            return create(type);
        }

        template<typename T>
        void Insert(T* t) {
            insert(t);
        }
    };
}

#endif /* !GUI_LAYOUTBUILDER_HPP */

