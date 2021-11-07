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

namespace Gui {
    class Button;
    class CheckBox;
    class Label;
    class NumberField;
    class Panel;
    class RadioButton;
    class TextInput;
    class Widget;
    class WidgetBase;
    class Window;

    template<typename T>
    struct Type {
        size_t hash;
    };

    class LayoutBuilder {
    protected:
        virtual Gui::Button* create(Type<Gui::Button> type) = 0;
        virtual Gui::CheckBox* create(Type<Gui::CheckBox> type) = 0;
        virtual Gui::Label* create(Type<Gui::Label> type) = 0;
        virtual Gui::NumberField* create(Type<Gui::NumberField> type) = 0;
        virtual Gui::Panel* create(Type<Gui::Panel> type) = 0;
        virtual Gui::RadioButton* create(Type<Gui::RadioButton> type) = 0;
        virtual Gui::TextInput* create(Type<Gui::TextInput> type) = 0;
        virtual Gui::Widget* create(Type<Gui::Widget> type) = 0;
        virtual Gui::Window* create(Type<Gui::Window> type) = 0;

        virtual void insert(Gui::WidgetBase*) = 0;
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

