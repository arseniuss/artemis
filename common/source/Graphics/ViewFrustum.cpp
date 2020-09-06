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

#include <glm/geometric.hpp>

#include <Graphics/ViewFrustum.hpp>

using namespace Graphics;

enum Planes {
    Near,
    Far,
    Left,
    Right,
    Top,
    Bottom,
};

float ViewFrustum::Plane::DistanceToPoint(const glm::vec3& point) const {
    return glm::dot(point, normal) + distanceToOrigin;
}

void ViewFrustum::Update(const glm::mat4& mat) noexcept {
    // Left
    _planes[Planes::Left].normal.x = mat[0][3] + mat[0][0];
    _planes[Planes::Left].normal.y = mat[1][3] + mat[1][0];
    _planes[Planes::Left].normal.z = mat[2][3] + mat[2][0];
    _planes[Planes::Left].distanceToOrigin = mat[3][3] + mat[3][0];

    // Right
    _planes[Planes::Right].normal.x = mat[0][3] - mat[0][0];
    _planes[Planes::Right].normal.y = mat[1][3] - mat[1][0];
    _planes[Planes::Right].normal.z = mat[2][3] - mat[2][0];
    _planes[Planes::Right].distanceToOrigin = mat[3][3] - mat[3][0];

    // Bottom
    _planes[Planes::Bottom].normal.x = mat[0][3] + mat[0][1];
    _planes[Planes::Bottom].normal.y = mat[1][3] + mat[1][1];
    _planes[Planes::Bottom].normal.z = mat[2][3] + mat[2][1];
    _planes[Planes::Bottom].distanceToOrigin = mat[3][3] + mat[3][1];

    // Top
    _planes[Planes::Top].normal.x = mat[0][3] - mat[0][1];
    _planes[Planes::Top].normal.y = mat[1][3] - mat[1][1];
    _planes[Planes::Top].normal.z = mat[2][3] - mat[2][1];
    _planes[Planes::Top].distanceToOrigin = mat[3][3] - mat[3][1];

    // Near
    _planes[Planes::Near].normal.x = mat[0][3] + mat[0][2];
    _planes[Planes::Near].normal.y = mat[1][3] + mat[1][2];
    _planes[Planes::Near].normal.z = mat[2][3] + mat[2][2];
    _planes[Planes::Near].distanceToOrigin = mat[3][3] + mat[3][2];

    // Far
    _planes[Planes::Far].normal.x = mat[0][3] - mat[0][2];
    _planes[Planes::Far].normal.y = mat[1][3] - mat[1][2];
    _planes[Planes::Far].normal.z = mat[2][3] - mat[2][2];
    _planes[Planes::Far].distanceToOrigin = mat[3][3] - mat[3][2];

    for (auto& plane : _planes) {
        float length = glm::length(plane.normal);
        plane.normal /= length;
        plane.distanceToOrigin /= length;
    }
}

bool ViewFrustum::ChunkIsInFrustum() const noexcept {
    return true; // TODO
}

