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

    class LayoutBuilder : public Gui::LayoutBuilder {
    protected:
        static std::map<size_t, std::function<void*(void) >> _registredWidgets;

        Gui::Widget* create(Gui::Type<Gui::Widget> type) override;
        Gui::Panel* create(Gui::Type<Gui::Panel> type) override;
        Gui::Button* create(Gui::Type<Gui::Button> type) override;
        Gui::Window* create(Gui::Type<Gui::Window> type) override;

        template<typename T>
        T* createUi() {
            int item = uiItem();
            void *data = uiAllocHandle(item, sizeof (T));
        
            T* t = new(data) T(item);
            
            return t;
        }
        
        void insert(Gui::Widget*) override;
        void insert(Gui::Panel*) override;
        void insert(Gui::Window*) override;
    public:
        LayoutBuilder(SDL_Window* window);
        ~LayoutBuilder();

        template<typename T, typename U>
        static void Add() {
            auto f = []() -> void* {
                int item = uiItem();
                U* data = (U *) uiAllocHandle(item, sizeof (U));

                data->item = item;

                return data;
            };

            _registredWidgets.emplace(typeid (T).hash_code(), f);
        }

      

    };
}

#endif /* !OPENGL_GUI_LAYOUTBUILDER_HPP */
