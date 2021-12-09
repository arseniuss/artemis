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
#include <Common/Debug.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Cameras/PerspectiveCamera.hpp>
#include <Graphics/Utils.hpp>

#include <glm/gtx/transform.hpp>

using namespace Graphics;

static unsigned int cameraIndex = 0;

bool Graphics::Camera::IsCameraHash(size_t hash) {
    return hash == Common::__hash<Graphics::Camera>() ||
            hash == Common::__hash<Graphics::PerspectiveCamera>();
}

void Camera::updateViewMatrix() {
    _viewMatrix = glm::translate(glm::mat4_cast(glm::conjugate(_orientation)), -_position);
}

Camera::Camera() : Object() {
    _name = "Camera #" + std::to_string(cameraIndex++);
}

Camera::~Camera() {

}

void Camera::SetPosition(glm::vec3 position) {
    Object::SetPosition(position);
    updateViewMatrix();
}

void Camera::SetOrientation(glm::quat orientation) {
    Object::SetOrientation(orientation);
    updateViewMatrix();
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return _projectionMatrix;
}

glm::mat4 Camera::GetViewMatrix() const {
    return _viewMatrix;
}

void Camera::LookAt(glm::vec3 target) {
    glm::vec3 up = {0, 1, 0};

    _orientation = glm::quatLookAt(glm::normalize(target - _position), up);
    _orientation = glm::normalize(_orientation);

    updateViewMatrix();
}

void Camera::UpdateProjectionMatrix() {

}
