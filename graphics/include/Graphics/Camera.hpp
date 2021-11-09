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

#include <Graphics/ViewFrustum.hpp>

#include <Graphics/Object.hpp>

namespace Graphics {

    class Camera : public Object {
    protected:        
        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;
    public:
        static bool IsCameraHash(size_t hash);
        
        Camera();
        virtual ~Camera();
        
        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewMatrix() const;
        
        virtual void UpdateProjectionMatrix();
    };
}

#endif /* !GRAPHICS_CAMERA_HPP */

