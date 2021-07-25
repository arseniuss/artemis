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

#ifndef GRAPHICS_MATERIAL_HPP
#define GRAPHICS_MATERIAL_HPP

#include <memory>
#include <vector>

namespace Graphics {
    class Material {
    protected:
        std::vector<std::weak_ptr<Material>> _materials;
    public:
        Material();
        
        bool IsVisible() const;
        bool IsArray() const;
        
        std::vector<std::weak_ptr<Material>>& GetMaterials();
    };
}

#endif /* !GRAPHICS_MATERIAL_HPP */
