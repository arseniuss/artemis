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

#include <sstream>

#include <SDL2/SDL_keycode.h>

#include <Common/Debug.hpp>
#include <Blendish/Blendish.hpp>
#include <NanoVG/NanoVG.hpp>
#include <OpenGL/Gui/Text.hpp>

#include "oui.h"

using namespace OpenGL;
using namespace Blendish;

TextInput::TextInput(int i) : OpenGLWidget(i) {
    uiSetSize(i, 0, BND_WIDGET_HEIGHT);
    uiSetEvents(i, UI_BUTTON0_DOWN | UI_KEY_DOWN | UI_CHAR);
}

Gui::TextInput* TextInput::SetText(const std::string& text) {
    _text = text;

    return this;
}

const std::string& TextInput::GetText() const {
    return _text;
}

void TextInput::Draw(NVG::NVGcontext* context) const {
    UIrect rect = uiGetRect(this->_id);
    BNDwidgetState state = (BNDwidgetState) uiGetState(this->_id);

    bndTextField(context, rect.x, rect.y, rect.w, rect.h, _corners, state,
            -1, _text.c_str(), _cursorStart, _cursorEnd);

    OpenGLWidget::Draw(context);
}

void TextInput::HandleEvent(UIevent event) {
    switch (event) {
        case UI_BUTTON0_DOWN:
        {
            UIrect rect = uiGetRect(this->_id);
            UIvec2 cursor = uiGetCursor();

            DEBUG("RECT " << rect.x << ", " << rect.y <<  "|" << rect.w << ", " << rect.h);
            DEBUG("CUR " << cursor.x << ", " << cursor.y);

            for (size_t i = 0; i < _text.size(); i++) {

            }

            uiFocus(this->_id);
            break;
        }
        case UI_KEY_DOWN:
        {
            unsigned int key = uiGetKey();

            switch (key) {
                case SDLK_RIGHT:
                    if (uiGetModifier() & KMOD_SHIFT) {
                        if (_cursorEnd < _text.size())
                            _cursorEnd++;
                    } else if (_cursorEnd < _text.size()) {
                        _cursorStart = _cursorEnd = _cursorEnd + 1;
                    } else {
                        _cursorStart = _cursorEnd = _text.size();
                    }
                    break;
                case SDLK_LEFT:
                    if (uiGetModifier() & KMOD_SHIFT) {
                        if (_cursorStart > 0)
                            _cursorStart--;
                    } else if (_cursorStart > 0) {
                        _cursorStart = _cursorEnd = _cursorStart - 1;
                    } else {
                        _cursorStart = _cursorEnd = 0;
                    }
                    break;
                case SDLK_BACKSPACE:
                {
                    std::stringstream ss;

                    if (_cursorEnd == _cursorStart && _cursorStart != 0) {
                        _cursorStart--;
                    }

                    for (size_t i = 0; i < _text.size(); i++) {
                        if (i < _cursorStart || i >= _cursorEnd) {
                            ss << _text[i];
                        }
                    }

                    _text = ss.str();
                    _cursorEnd = _cursorStart;
                    break;
                }
                case SDLK_RETURN:
                    uiFocus(-1);
            }
            break;
        }
        case UI_CHAR:
            break;
        default:
            break;
    }
}


