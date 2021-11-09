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

#ifndef GRAPHICS_OBJECTS_POINTS_HPP
#define GRAPHICS_OBJECTS_POINTS_HPP

#include <memory>

#include <Graphics/ViewObject.hpp>

namespace Graphics {
    class Geometry;
    class Material;

    class Points : public ViewObject {
    protected:

    public:
        static size_t Hash;

        Points(std::shared_ptr<Geometry> geo, std::shared_ptr<Material> mat);
        virtual ~Points();

    };
}

#endif /* !GRAPHICS_OBJECTS_POINTS_HPP */
