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

#include <experimental/filesystem>

#include <Blendish/Blendish.hpp>
#include <NanoVG/NanoVG.hpp>
#include <OpenGL/Context.hpp>
#include <OpenGL/Debug.hpp>
#include <OpenGL/Gui/LayoutBuilder.hpp>
#include <glad.h>
#include <oui.h>

#include "OpenGL/Gui/Widget.hpp"

using namespace std;

using namespace OpenGL;

const string& fontFilename = "data/DejaVuSans.ttf";
const string& iconFilename = "data/blender_icons16.png";

Context::Context(const std::string& title) : Graphics::Context(title, SDL_WINDOW_OPENGL) {
    int w, h;
    GLuint VertexArrayID;

    _context = SDL_GL_CreateContext(_window);
    if (_context == nullptr) {
        throw runtime_error("Cannot create GL context!");
    }

    SDL_GetWindowSize(_window, &w, &h);

    gladLoadGL();

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, w, h);
    glDepthFunc(GL_LESS);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    uiMakeCurrent(uiCreateContext(4096, 1 << 20));

    _nvgContext = NVG::nvgCreateGL3(NVG::NVG_ANTIALIAS);

    if (!std::experimental::filesystem::exists(fontFilename))
        throw runtime_error("Font file not found: " + fontFilename);

    if (!std::experimental::filesystem::exists(iconFilename))
        throw runtime_error("Icon file not found: " + iconFilename);

    Blendish::bndSetFont(nvgCreateFont(_nvgContext, "system", fontFilename.c_str()));
    Blendish::bndSetIconImage(nvgCreateImage(_nvgContext, iconFilename.c_str(), 0));
}

Context::~Context() {
    SDL_GL_DeleteContext(_context);
}

void Context::Render() {
    int w, h;

    SDL_GetWindowSize(_window, &w, &h);

    glClearColor(0.2, 0.4, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    for (Graphics::DrawFunc func : _drawables) {
        func(*this);
        CheckOpenGLErrors();
    }

    if (uiGetItemCount() > 0) {
        NVG::nvgBeginFrame(_nvgContext, w, h, w / h);

        DrawLayout(0, Blendish::BND_CORNER_NONE);

        NVG::nvgEndFrame(_nvgContext);
    }

    SDL_GL_SwapWindow(_window);
}

void Context::BuildLayout(std::function<void(Gui::LayoutBuilder&)> build) {
    OpenGL::LayoutBuilder builder;
    
    build(builder);
}

void Context::DrawLayout(int item, int corners) {
    const OpenGL::Widget* widget = (const OpenGL::Widget *)uiGetHandle(item);
    
    if(widget) widget->Draw(this->_nvgContext);
}


