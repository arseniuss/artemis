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
#include <memory>

#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_keyboard.h>

#include <Blendish/Blendish.hpp>
#include <Graphics/Material.hpp>
#include <NanoVG/NanoVG.hpp>
#include <OpenGL/Context.hpp>
#include <OpenGL/Debug.hpp>
#include <OpenGL/Gui/LayoutBuilder.hpp>
#include <OpenGL/Gui/Widget.hpp>
#include <OpenGL/Renderer.hpp>
#include <glad.h>
#include <oui.h>

using namespace std;

using namespace OpenGL;

const string& fontFilename = "data/DejaVuSans.ttf";
const string& iconFilename = "data/blender_icons16.png";

void ui_handler(int item, UIevent event) {
    OpenGLWidget* w = (OpenGLWidget *) uiGetHandle(item);

    if (w) {
        w->HandleEvent(event);
    }
}

bool Context::Debug = false;
std::shared_ptr<Context> Context::Instance;

Context::Context(const std::string& title,
        std::shared_ptr<const Common::Config> config) :
Graphics::Context(title, config, SDL_WINDOW_OPENGL) {
    int w, h;
    GLuint VertexArrayID;

    Debug = config->Get<bool>("Graphics", "Debug", false);

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
    uiSetHandler(&ui_handler);

    _nvgContext = NVG::nvgCreateGL3(NVG::NVG_ANTIALIAS);

    if (!std::experimental::filesystem::exists(fontFilename))
        throw runtime_error("Font file not found: " + fontFilename);

    if (!std::experimental::filesystem::exists(iconFilename))
        throw runtime_error("Icon file not found: " + iconFilename);

    Blendish::bndSetFont(nvgCreateFont(_nvgContext, "system", fontFilename.c_str()));
    Blendish::bndSetIconImage(nvgCreateImage(_nvgContext, iconFilename.c_str(), 0));

    _renderer = std::make_unique<OpenGL::Renderer>(*this);
}

Context::~Context() {
    SDL_GL_DeleteContext(_context);
}

void Context::HandleInput() {
    int mousex, mousey;
    uint32_t mouse, mod;

    mouse = SDL_GetMouseState(&mousex, &mousey);
    mod = SDL_GetModState();

    uiSetCursor(mousex, mousey);

    uiSetButton(0, mod, mouse & SDL_BUTTON_LMASK ? 1 : 0);
    uiSetButton(1, mod, mouse & SDL_BUTTON_MMASK ? 1 : 0);
    uiSetButton(2, mod, mouse & SDL_BUTTON_RMASK ? 1 : 0);
}

bool Context::HandleEvent(SDL_Event& event) {
    uint32_t mod = SDL_GetModState();

    switch (event.type) {
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            uiSetKey(event.key.keysym.sym, mod,
                    event.key.type == SDL_KEYUP);
            return true;
    }

    return false;
}

void Context::Update(float deltaTime) {
    int w, h;

    SDL_GetWindowSize(this->_window, &w, &h);

    uiSetSize(0, w, h);

    uiProcess(deltaTime);
}

void Context::BuildLayout(std::function<void(Gui::LayoutBuilder&) > build) {
    OpenGL::LayoutBuilder builder(Instance);

    build(builder);
}

void Context::DrawLayout() {
    int w, h;

    SDL_GetWindowSize(_window, &w, &h);

    if (uiGetItemCount() > 0) {
        NVG::nvgBeginFrame(_nvgContext, w, h, (float) w / (float) h);

        drawLayout(0, Blendish::BND_CORNER_NONE);

        NVG::nvgEndFrame(_nvgContext);
    }
}

void Context::drawLayout(int item, int corners) {
    const OpenGLWidget* widget = static_cast<const OpenGLWidget*> (uiGetHandle(item));

    if (uiGetState(item) == UI_FROZEN) {
        nvgGlobalAlpha(_nvgContext, BND_DISABLED_ALPHA);
    }

    if (widget) {
        widget->Draw(_nvgContext);
    }

    int kid = uiFirstChild(item);
    while (kid > 0) {
        drawLayout(kid, corners);

        kid = uiNextSibling(kid);
    }

    if (uiGetState(item) == UI_FROZEN) {
        nvgGlobalAlpha(_nvgContext, 1.0);
    }
}

std::shared_ptr<Graphics::Renderer> Context::GetRenderer() {
    return _renderer;
}
