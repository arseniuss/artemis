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

#ifndef GRAPHICS_VIEWFRUSTUM_HPP
#define GRAPHICS_VIEWFRUSTUM_HPP

#include <array>

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

namespace Graphics {
    class ViewFrustum {
    private:
        struct Plane {
            float DistanceToPoint(const glm::vec3& point) const;
            
            float distanceToOrigin;
            glm::vec3 normal;
        };
        
        std::array<Plane, 6> _planes;
    public:
        void Update(const glm::mat4& projViewMatrix) noexcept;
        
        bool ChunkIsInFrustum(/* TODO */) const noexcept;
    };
}

#endif /* !GRAPHICS_VIEWFRUSTUM_HPP */
