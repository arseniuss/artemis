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

#include <string>

#include <OpenGL/Context.hpp>
#include <OpenGL/Gui/LayoutBuilder.hpp>
#include <OpenGL/Gui/Widget.hpp>
#include <OpenGL/Gui/Panel.hpp>


extern "C" {

    void InitGraphics(void) {
        OpenGL::LayoutBuilder::Add<Gui::Widget, OpenGL::Widget>();
        OpenGL::LayoutBuilder::Add<Gui::Panel, OpenGL::Panel>();
    }

    OpenGL::Context* CreateContext(const std::string& title) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        return new OpenGL::Context(title);
    }
}