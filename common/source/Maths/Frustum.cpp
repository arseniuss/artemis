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

#include <Maths/Frustum.hpp>

using namespace Maths;

enum Planes {
    Near,
    Far,
    Left,
    Right,
    Top,
    Bottom
};

void Frustum::Update(const glm::mat4& mat) {
    _planes[Planes::Left]
            .Set(mat[0][3] + mat[0][0], mat[1][3] + mat[1][0], mat[2][3] + mat [2][0], mat[3][3] + mat[3][0])
            .Normalize();
    _planes[Planes::Right]
            .Set(mat[0][3] - mat[0][0], mat[1][3] - mat[1][0], mat[2][3] - mat[2][0], mat[3][3] - mat[3][0])
            .Normalize();
    _planes[Planes::Bottom]
            .Set(mat[0][3] + mat[0][1], mat[1][3] + mat[1][1], mat[2][3] + mat[2][1], mat[3][3] + mat[3][1])
            .Normalize();
    _planes[Planes::Top]
            .Set(mat[0][3] - mat[0][1], mat[1][3] - mat[1][1], mat[2][3] - mat[2][1], mat[3][3] - mat[3][1])
            .Normalize();
    _planes[Planes::Near]
            .Set(mat[0][3] + mat[0][2], mat[1][3] + mat[1][2], mat[2][3] + mat[2][2], mat[3][3] + mat[3][2])
            .Normalize();
    _planes[Planes::Far]
            .Set(mat[0][3] - mat[0][2], mat[1][3] - mat[1][2], mat[2][3] - mat[2][2], mat[3][3] - mat[2][3])
            .Normalize();
}

