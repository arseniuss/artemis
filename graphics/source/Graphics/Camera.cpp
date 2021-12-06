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

#include <Common.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Cameras/PerspectiveCamera.hpp>
#include <Graphics/Utils.hpp>

using namespace Graphics;

static unsigned int cameraIndex = 0;

bool Graphics::Camera::IsCameraHash(size_t hash) {
    return hash == Common::__hash<Graphics::Camera>() ||
            hash == Common::__hash<Graphics::PerspectiveCamera>();
}

Camera::Camera() {
    _name = "Camera #" + std::to_string(cameraIndex++);

    _viewMatrix = glm::lookAt(glm::vec3(4, 3, 3),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0));
}

Camera::~Camera() {

}

glm::mat4 Camera::GetProjectionMatrix() const {
    return _projectionMatrix;
}

glm::mat4 Camera::GetViewMatrix() const {
    return _viewMatrix;
}

void Camera::UpdateProjectionMatrix() {

}

