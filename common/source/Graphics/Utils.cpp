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

#include <glm/gtc/matrix_transform.hpp>

#include <Graphics/Utils.hpp>

namespace Graphics {

    glm::mat4 CreateProjectionViewMatrix(const glm::vec3& position,
            const glm::vec3& rotation,
            const glm::mat4& projection) {

        glm::mat4 view{1.0f};
        glm::mat4 projectionView{1.0f};

        RotateMatrix(view, rotation);
        TranslateMatrix(view, -position);
        projectionView = projection * view;

        return projectionView;
    }

    void RotateMatrix(glm::mat4& matrix, const glm::vec3& degrees) {
        matrix = glm::rotate(matrix, glm::radians(degrees.x),{1, 0, 0});
        matrix = glm::rotate(matrix, glm::radians(degrees.y),{0, 1, 0});
        matrix = glm::rotate(matrix, glm::radians(degrees.z),{0, 0, 1});
    }

    void TranslateMatrix(glm::mat4& matrix, const glm::vec3& offset) {
        matrix = glm::translate(matrix, offset);
    }
}
