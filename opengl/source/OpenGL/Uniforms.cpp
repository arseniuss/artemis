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


#include <glm/gtx/string_cast.hpp>

#include <OpenGL/Debug.hpp>
#include <OpenGL/Uniforms.hpp>

using namespace OpenGL;

Uniforms::Uniforms() {

}

Uniforms::Uniforms(GLuint programId) {

}

Uniforms::~Uniforms() {

}

void Uniforms::Set(const std::string& name, bool value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = std::to_string(value);
    GL_CHECK2(glUniform1i, _data[name].location, (int) value);
}

void Uniforms::Set(const std::string& name, int value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = std::to_string(value);
    GL_CHECK2(glUniform1i, _data[name].location, value);
}

void Uniforms::Set(const std::string& name, unsigned int value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = std::to_string(value);
    GL_CHECK2(glUniform1ui, _data[name].location, value);
}

void Uniforms::Set(const std::string& name, float value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = std::to_string(value);
    GL_CHECK2(glUniform1f, _data[name].location, value);
}

void Uniforms::Set(const std::string& name, double value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = std::to_string(value);
    GL_CHECK2(glUniform1d, _data[name].location, value);
}

void Uniforms::Set(const std::string& name, glm::vec2 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = glm::to_string(value);
    GL_CHECK2(glUniform2fv, _data[name].location, 1, &value[0]);
}

void Uniforms::Set(const std::string& name, glm::vec3 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = glm::to_string(value);
    GL_CHECK2(glUniform3fv, _data[name].location, 1, &value[0]);
}

void Uniforms::Set(const std::string& name, glm::vec4 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = glm::to_string(value);
    GL_CHECK2(glUniform4fv, _data[name].location, 1, &value[0]);
}

void Uniforms::Set(const std::string& name, glm::mat2 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = glm::to_string(value);
    GL_CHECK2(glUniformMatrix2fv, _data[name].location, 1, GL_FALSE, &value[0][0]);
}

void Uniforms::Set(const std::string& name, glm::mat3 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = glm::to_string(value);
    GL_CHECK2(glUniformMatrix3fv, _data[name].location, 1, GL_FALSE, &value[0][0]);
}

void Uniforms::Set(const std::string& name, glm::mat4 value) {
    if (!_data.contains(name))
        throw std::runtime_error("Unknown uniform " + name);
    _data[name].isSet = true;
    _data[name].value = glm::to_string(value);
    GL_CHECK2(glUniformMatrix4fv, _data[name].location, 1, GL_FALSE, &value[0][0]);
}

bool Uniforms::Exists(const std::string& name) const {
    return _data.contains(name);
}

bool Uniforms::Dump() {
    for (auto p : _data) {
        DEBUG("[DEBUG] " << p.first << " " << (p.second.isSet ? "is set" : "is not set") << " "
                << (p.second.isSet ? p.second.value : ""));
    }
    
    return true;
}

