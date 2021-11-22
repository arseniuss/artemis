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

#ifndef GRAPHICS_COLOR_HPP
#define GRAPHICS_COLOR_HPP

#include <glm/glm.hpp>

#include <Graphics/Property.hpp>

namespace Graphics {

    class Color : public Property {
    private:
        glm::vec4 _value;
    public:
        static size_t Hash;
        static Color Rgb(uint32_t value);
        
        float& r;
        float& g;
        float& b;
        float& a;

        Color();
        Color(float r, float g, float b, float a = 0);
        
        Color& operator=(const Color& other);
        
        glm::vec4 GetVector() const;
    };
}

#endif /* !GRAPHICS_COLOR_HPP */
