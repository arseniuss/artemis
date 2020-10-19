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

#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include <string>

#include <glm/glm.hpp>

#include <Graphics/Buffer.hpp>

namespace Graphics {

    class Shader {
    public:
        virtual void Use() = 0;

        virtual void Draw() = 0;

        virtual void SetUniform(const std::string& name,
                const glm::mat4 value, bool transpose = false) = 0;

        virtual void SetBuffer(const std::string& name,
                const Buffer* buffer) = 0;
    };
}

#endif /* !GRAPHICS_SHADER_HPP */
