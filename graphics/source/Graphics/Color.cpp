/**
 *  Artemis game
 *  Copyright (C) 2021 Armands Arseniuss Skolmeisters
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

#include <Graphics/Color.hpp>

using namespace Graphics;

size_t Color::Hash = typeid (Color).hash_code();

Color Color::Rgb(uint32_t value) {
    uint8_t red = (value >> 16) & 0xFF;
    uint8_t green = (value >> 8) & 0xFF;
    uint8_t blue = value & 0xFF;

    return Color(red / 255.0, green / 255.0, blue / 255.0);
}

Color::Color() : r(_value.r), g(_value.g), b(_value.b), a(_value.a) {
    _value = {0, 0, 0, 0};
    _hash = Color::Hash;
}

Color::Color(float r, float g, float b, float a) : Color() {
    _value = {r, g, b, a};
}

Color& Color::operator=(const Color& other) {
    _value = other._value;

    return *this;
}

glm::vec4 Color::GetVector() const {
    return _value;
}
