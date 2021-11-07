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

#ifndef GRAPHICS_VIEWOBJECT_HPP
#define GRAPHICS_VIEWOBJECT_HPP

#include <Graphics/Object.hpp>

namespace Graphics {
    class Geometry;
    class Material;

    class ViewObject : public Object {
    protected:
        std::shared_ptr<Geometry> _geo;
        std::shared_ptr<Material> _mat;
    public:
        ViewObject(std::shared_ptr<Geometry> geo, std::shared_ptr<Material> mat);

        std::shared_ptr<Geometry> GetGeometry() {
            return _geo;
        }

        std::shared_ptr<Material> GetMaterial() {
            return _mat;
        }
    };
}

#endif /* !GRAPHICS_VIEWOBJECT_HPP */
