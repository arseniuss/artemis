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

static unsigned int cameraIndex = 0;

Camera::Camera() {
    _name = "Camers #" + std::to_string(cameraIndex++);
    _projMatrix = glm::mat4{1.0f};
    _matrixWorldInverse = glm::mat4{1.0f};
}

const glm::mat4& Camera::GetMatrixWorldInverse() const {
    return _matrixWorldInverse;
}

const glm::mat4& Camera::GetProjectionMatrix() const {
    return _projMatrix;
}
