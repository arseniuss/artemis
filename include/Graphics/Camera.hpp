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

#ifndef GRAPHICS_CAMERA_HPP
#define GRAPHICS_CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include <World/Entity.hpp>
#include <Graphics/ViewFrustum.hpp>

#include <Graphics/Object.hpp>

namespace Graphics {

    class Camera : public Object {
    protected:
        glm::mat4 _matrixWorldInverse;
        glm::mat4 _projMatrix;
        glm::mat4 _projMatrixInverse;
    public:
        Camera();
        
        const glm::mat4& GetProjectionMatrix() const;
        
        const glm::mat4& GetMatrixWorldInverse() const;
    };
}

#endif /* !GRAPHICS_CAMERA_HPP */

