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

#ifndef INTERNAL_HPP
#define INTERNAL_HPP

#include <Gui/Oui.hpp>
#include <NanoVG/NanoVG.hpp>

namespace Gui {

    typedef struct {
        UIData head;
        const char *label;
        NVG::NVGcolor color;
    } UIRectData;

    typedef struct {
        UIData head;
        int iconId;
        const char *label;
    } UIButtonData;

    typedef struct {
        UIData head;
        const char *label;
        int *option;
    } UICheckData;

    typedef struct {
        UIData head;
        int iconId;
        const char *label;
        int *value;
    } UIRadioData;

    typedef struct {
        UIData head;
        const char *label;
        float *progress;
    } UISliderData;

    typedef struct {
        UIData head;
        char *text;
        int maxsize;
    } UITextData;

    int Button(int iconId, const char *label, UIHandlerFunc handler);
    int Panel();
    int Radio(int iconId, const char *label, int* value);
}

#endif /* INTERNAL_HPP */

