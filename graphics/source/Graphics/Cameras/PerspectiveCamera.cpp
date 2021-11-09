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

#include <Graphics/Cameras/PerspectiveCamera.hpp>

using namespace Graphics;

PerspectiveCamera::PerspectiveCamera() {
    _fov = 50.0f;
    _aspect = 1.0f;
    _nearPlane = 0.1f;
    _farPlane = 2000.0f;

    UpdateProjectionMatrix();
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float nearPlane, float farPlane) {
    _fov = fov;
    _aspect = aspect;
    _nearPlane = nearPlane;
    _farPlane = farPlane;

    UpdateProjectionMatrix();
}

void PerspectiveCamera::UpdateProjectionMatrix() {
    _projectionMatrix = glm::perspective(_fov, _aspect, _nearPlane, _farPlane);
}


