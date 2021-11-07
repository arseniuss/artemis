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

#ifndef GRAPHICS_OBJECTS_LINE_HPP
#define GRAPHICS_OBJECTS_LINE_HPP

#include <Graphics/ViewObject.hpp>

namespace Graphics {

    class Line : public ViewObject {
    private:
        float _lineWidth;

        bool _isLineLoop;
        bool _isLineSegments;
    public:
        static size_t Hash;

        Line(std::shared_ptr<Geometry> geo, std::shared_ptr<Material> mat);

        float GetLineWidth() const;

        bool IsLineSegments() const;
        bool IsLineLoop() const;
    };
}

#endif /* !GRAPHICS_OBJECTS_LINE_HPP */
