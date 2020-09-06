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

#include <glm/ext/matrix_clip_space.hpp>

#include <Graphics/Camera.hpp>
#include <Graphics/Utils.hpp>

using namespace Graphics;

Camera::Camera(float w, float h) {
    _projectionMatrix = glm::perspective(3.14f / 2.0f, w / h, 0.01f, 2000.0f);
}

void Camera::Update(World::Entity& entity) {
    _frustum.Update(_projectionViewMatrix);
    _position = entity.position;
    _rotation = entity.rotation;

    _projectionViewMatrix =
            CreateProjectionViewMatrix(_position, _rotation, _projectionMatrix);
}

const ViewFrustum& Camera::GetFrustum() const {
    return _frustum;
}

const glm::vec3& Camera::GetPosition() const {
    return _position;
}

const glm::mat4& Camera::GetProjectionView() const {
    return _projectionViewMatrix;
}
