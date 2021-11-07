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

#include <OpenGL/Uniforms.hpp>

using namespace OpenGL;

Uniforms::Uniforms(GLuint programId) {

}

Uniforms::~Uniforms() {

}

void Uniforms::Set(const std::string& name, bool value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniform1i(_data[name].location, (int) value);
}

void Uniforms::Set(const std::string& name, int value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniform1i(_data[name].location, value);
}

void Uniforms::Set(const std::string& name, unsigned int value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniform1ui(_data[name].location, value);
}

void Uniforms::Set(const std::string& name, float value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniform1f(_data[name].location, value);
}

void Uniforms::Set(const std::string& name, double value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniform1d(_data[name].location, value);
}

void Uniforms::Set(const std::string& name, glm::vec2 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniform2fv(_data[name].location, 1, &value[0]);
}

void Uniforms::Set(const std::string& name, glm::vec3 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniform3fv(_data[name].location, 1, &value[0]);
}

void Uniforms::Set(const std::string& name, glm::vec4 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniform4fv(_data[name].location, 1, &value[0]);
}

void Uniforms::Set(const std::string& name, glm::mat2 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniformMatrix2fv(_data[name].location, 1, GL_FALSE, &value[0][0]);
}

void Uniforms::Set(const std::string& name, glm::mat3 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniformMatrix3fv(_data[name].location, 1, GL_FALSE, &value[0][0]);
}

void Uniforms::Set(const std::string& name, glm::mat4 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    glUniformMatrix4fv(_data[name].location, 1, GL_FALSE, &value[0][0]);
}


