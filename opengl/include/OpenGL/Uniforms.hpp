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

#ifndef OPENGL_UNIFORMS_HPP
#define OPENGL_UNIFORMS_HPP

#include <map>
#include <string>

#include <glm/glm.hpp>

#include <Common/Dictionary.hpp>

#include "glad.h"

namespace OpenGL {

    struct Uniform {
        int location;
        size_t hash;
        size_t size;

        bool isSet = false;
        std::string value;
    };

    class Uniforms {
    protected:
        unsigned int _programId;
        std::map<std::string, Uniform> _data;
    public:
        Uniforms();
        Uniforms(GLuint programId);
        ~Uniforms();

        template<typename T>
        void Add(int location, const std::string& name, size_t size) {
            if (_data.contains(name))
                throw std::runtime_error("Uniform exists");

            _data.emplace(name, Uniform{location, typeid (T).hash_code(), size});
        }

        void Set(const std::string& name, bool value);

        void Set(const std::string& name, int value);
        void Set(const std::string& name, unsigned int value);

        void Set(const std::string& name, float value);
        void Set(const std::string& name, double value);

        void Set(const std::string& name, glm::vec2 value);
        void Set(const std::string& name, glm::vec3 value);
        void Set(const std::string& name, glm::vec4 value);

        void Set(const std::string& name, glm::mat2 value);
        void Set(const std::string& name, glm::mat3 value);
        void Set(const std::string& name, glm::mat4 value);

        bool Exists(const std::string& name) const;

        bool Dump();
    };

}

#endif /* !OPENGL_UNIFORMS_HPP */
