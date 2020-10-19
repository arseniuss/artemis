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

#include <fstream>
#include <experimental/filesystem>

#include <OpenGL/Buffer.hpp>
#include <OpenGL/Debug.hpp>
#include <OpenGL/Shader.hpp>

using namespace OpenGL;

const std::vector<std::tuple<std::string, GLenum>> shaderTypes = {
    {".frag", GL_FRAGMENT_SHADER},
    {".vert", GL_VERTEX_SHADER},
    {".geom", GL_GEOMETRY_SHADER},
    {".comp", GL_COMPUTE_SHADER}
};

Shader::Shader(const std::string& name) {
    std::vector<GLuint> shaders;

    _id = glCreateProgram();

    for (auto it = shaderTypes.cbegin(); it < shaderTypes.cend(); it++) {
        const std::string filename = "data/shaders/" + name + std::get<0>(*it);

        if (std::experimental::filesystem::exists(filename)) {
            GLuint shader = create(filename, std::get<1>(*it));

            glAttachShader(_id, shader);

            shaders.emplace_back(shader);
        }
    }

    if (shaders.empty()) {
        throw std::runtime_error("No shaders to build program with");
    }

    glLinkProgram(_id);

    for (GLuint shader : shaders) {
        glDetachShader(_id, shader);
        glDeleteShader(shader);
    }
}

GLuint Shader::create(const std::string& filename, GLenum shaderType) {
    GLuint id = glCreateShader(shaderType);
    std::string code;
    std::ifstream s(filename, std::ios::in);

    if (s.is_open()) {
        std::stringstream ss;

        ss << s.rdbuf();
        code = ss.str();
        s.close();
    } else {
        std::string msg = "Cannot open shader file " + filename;

        throw std::runtime_error(msg.c_str());
    }

    const char *codePtr = code.c_str();

    glShaderSource(id, 1, &codePtr, NULL);
    glCompileShader(id);

    GLint result = GL_FALSE;
    int infoLength;

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLength);
    if (infoLength > 0) {
        std::string info;

        info.resize(infoLength + 1);

        glGetShaderInfoLog(id, infoLength, NULL, &info[0]);

        std::string msg = "Shader " + filename + " error: " + info;

        throw std::runtime_error(msg);
    }

    return id;
}

void Shader::Use() {
    glUseProgram(_id);
}

void Shader::Draw() {
    glDrawArrays(GL_TRIANGLES, 0, 12*3); 
}

void Shader::SetUniform(const std::string& name, const glm::mat4 value,
        bool transpose) {
    GLuint uid = glGetUniformLocation(_id, name.c_str());

    if (uid == (GLuint) - 1) {
        std::string msg = "Cannot find uniform " + name;

        throw std::runtime_error(msg);
    }

    glUniformMatrix4fv(uid, 1, (transpose ? GL_TRUE : GL_FALSE), &value[0][0]);

    CheckOpenGLErrors();
}

void Shader::SetBuffer(const std::string& name, const Graphics::Buffer* buffer) {
    const OpenGL::Buffer* b = (OpenGL::Buffer *)buffer;
    GLint aid = glGetAttribLocation(_id, name.c_str());

    if (aid == -1) {
        std::string msg = "Cannot find attr " + name;

        throw std::runtime_error(msg);
    }

    glEnableVertexAttribArray(aid);
    b->Use();
    glVertexAttribPointer(
            aid,
            3, // TODO: size
            GL_FLOAT, // TODO: type
            GL_FALSE, // TODO: normalized
            0, // TODO: stride
            (void *) 0
            );

    CheckOpenGLErrors();
}


