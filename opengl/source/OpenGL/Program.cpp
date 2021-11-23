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

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <numeric>
#include <regex>
#include <vector>

#include <glm/glm.hpp>

#include <Common/Debug.hpp>
#include <OpenGL/Debug.hpp>
#include <OpenGL/Program.hpp>
#include <OpenGL/Uniforms.hpp>
#include <Utility/Filesystem.hpp>
#include <Utility/String.hpp>

#include "glad.h"

using namespace OpenGL;

Program::Program() : _uniforms() {
    GL_CHECK(_id = glCreateProgram());
    _uniforms = Uniforms(_id);
}

Program::~Program() {
    GL_CHECK2(glDeleteProgram, _id);
}

std::string Program::generatePrecision(const MaterialProperties& props) {
    std::string str = "";
    std::string precision = props.GetPrecision();

    if (!precision.empty()) {
        str = "precision " + precision + " float;\nprecision " + precision + " int;";

        if (precision == "highp") {
            str += "\n#define HIGH_PRECISION";
        } else if (precision == "mediump") {
            str += "\n#define MEDIUM_PRECISION";
        } else if (precision == "lowp") {
            str += "\n#define LOW_PRECISION";
        }
    }

    return str;
}

std::string Program::resolveIncludes(std::string& text) {
    return Utility::RegexReplace(text, "[ \\t]*#include +<(.*)>",
            [](std::string match, const std::vector<std::string>& groups) {
                std::string include = groups[1];

                return Utility::LoadFullFile("data/snips/" + include + "_inc.glsl");
            });
}

GLuint Program::compilerShader(GLenum shader_type, const std::string& source) {
    GLuint shader;
    GLint test;
    const char *src = source.data();

    GL_CHECK(shader = glCreateShader(shader_type));
    GL_CHECK2(glShaderSource, shader, 1, &src, nullptr);

    GL_CHECK2(glCompileShader, shader);

    GL_CHECK2(glGetShaderiv, shader, GL_COMPILE_STATUS, &test);
    if (!test) {
        std::vector<char> log(BUFSIZ);

        GL_CHECK2(glGetShaderInfoLog, shader, log.size(), nullptr, &log[0]);
        DEBUG("Compilation failed: " << &log[0]);
        throw std::runtime_error(std::string(&log[0]));
    }

    return shader;
}

void Program::createProgram(const std::string& vertexSource, const std::string& fragmentSource) {
    GLuint vertexShader = compilerShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compilerShader(GL_FRAGMENT_SHADER, fragmentSource);

    GL_CHECK2(glAttachShader, _id, vertexShader);
    GL_CHECK2(glAttachShader, _id, fragmentShader);

    GL_CHECK2(glLinkProgram, _id);

    GL_CHECK2(glDeleteShader, vertexShader);
    GL_CHECK2(glDeleteShader, fragmentShader);
}

void Program::updateAttributes() {
    int count;

    GL_CHECK2(glGetProgramiv, _id, GL_ACTIVE_ATTRIBUTES, &count);

    DEBUG("Attribute count: " << count);

    for (int i = 0; i < count; i++) {
        char name[80] = {0};

        GLsizei len = 0;
        GLint size = 0;
        GLenum type = 0;

        GL_CHECK2(glGetActiveAttrib, _id, (GLuint) i, sizeof (name), &len, &size, &type, name);

        DEBUG("Attribute #" << i << ": name=\"" << name << "\"(" << len << ")" << " type=" << type << " size=" << size);

        size_t type_hash = 0;

        switch (type) {
            case GL_FLOAT: type_hash = typeid (float).hash_code();
                break;
            case GL_FLOAT_VEC2: type_hash = typeid (glm::vec2).hash_code();
                break;
            case GL_FLOAT_VEC3: type_hash = typeid (glm::vec3).hash_code();
                break;
            case GL_FLOAT_VEC4: type_hash = typeid (glm::vec4).hash_code();
                break;

            case GL_FLOAT_MAT2: type_hash = typeid (glm::mat2).hash_code();
                break;
            case GL_FLOAT_MAT3: type_hash = typeid (glm::mat3).hash_code();
                break;
            case GL_FLOAT_MAT4: type_hash = typeid (glm::mat4).hash_code();
                break;

            case GL_DOUBLE: type_hash = typeid (double).hash_code();
                break;
            case GL_DOUBLE_VEC2: type_hash = typeid (glm::dvec2).hash_code();
                break;
            case GL_DOUBLE_VEC3: type_hash = typeid (glm::dvec3).hash_code();
                break;
            case GL_DOUBLE_VEC4: type_hash = typeid (glm::dvec4).hash_code();
                break;

            case GL_DOUBLE_MAT2: type_hash = typeid (glm::dmat2).hash_code();
                break;
            case GL_DOUBLE_MAT3: type_hash = typeid (glm::dmat3).hash_code();
                break;
            case GL_DOUBLE_MAT4: type_hash = typeid (glm::dmat4).hash_code();
                break;
            default:
                throw std::runtime_error(std::string("Unrecognised attribute type: ") + std::to_string(type));
                break;
        }

        int location;

        GL_CHECK(location = glGetAttribLocation(_id, name));

        _attributes.emplace(name, ProgramAttribute{location, type_hash});
    }
}

void Program::updateUniforms() {
    int count;

    GL_CHECK2(glGetProgramiv, _id, GL_ACTIVE_UNIFORMS, &count);

    DEBUG("Uniform count: " << count);

    for (int i = 0; i < count; i++) {
        char name[80] = {0};

        GLsizei len = 0;
        GLint size = 0;
        GLenum type = 0;

        GL_CHECK2(glGetActiveUniform, _id, (GLuint) i, sizeof (name), &len, &size, &type, name);

        DEBUG("Uniform #" << i << ": name=\"" << name << "\"(" << len << ")" << " type=" << type << " size=" << size);

        switch (type) {
            case GL_FLOAT: _uniforms.Add<float>(i, name, size);
                break;
            case GL_FLOAT_VEC2: _uniforms.Add<glm::vec2>(i, name, size);
                break;
            case GL_FLOAT_VEC3: _uniforms.Add<glm::vec3>(i, name, size);
                break;
            case GL_FLOAT_VEC4: _uniforms.Add<glm::vec4>(i, name, size);
                break;

            case GL_FLOAT_MAT2: _uniforms.Add<glm::mat2>(i, name, size);
                break;
            case GL_FLOAT_MAT3: _uniforms.Add<glm::mat3>(i, name, size);
                break;
            case GL_FLOAT_MAT4: _uniforms.Add<glm::mat4>(i, name, size);
                break;

            case GL_DOUBLE: _uniforms.Add<double>(i, name, size);
                break;
            case GL_DOUBLE_VEC2: _uniforms.Add<glm::dvec2>(i, name, size);
                break;
            case GL_DOUBLE_VEC3: _uniforms.Add<glm::dvec3>(i, name, size);
                break;
            case GL_DOUBLE_VEC4: _uniforms.Add<glm::dvec4>(i, name, size);
                break;

            case GL_DOUBLE_MAT2: _uniforms.Add<glm::dmat2>(i, name, size);
                break;
            case GL_DOUBLE_MAT3: _uniforms.Add<glm::dmat3>(i, name, size);
                break;
            case GL_DOUBLE_MAT4: _uniforms.Add<glm::dmat4>(i, name, size);
                break;

            default:
                throw std::runtime_error(std::string("Unrecognised uniform type: ") + std::to_string(type));
        }
    }
}

void Program::Build(const MaterialProperties& props) {
    std::string vertextShaderContent = props.GetVertextShaderText();
    std::string fragmentShaderContent = props.GetFragmentShaderText();

    std::string versionString = "";

    if (!props.GetGLSLVersion().empty()) {
        versionString = "#version " + props.GetGLSLVersion() + "\n";
    }

    std::vector<std::string> prefixVector = {
        //generatePrecision(props),
        "#define VERTEX_SHADER",
        "#define SHADER_NAME " + props.GetName() + "_vertex",
        props.HasVertexColor() ? "#define USE_COLOR" : "",
        "uniform mat4 modelMatrix;",
        "uniform mat4 modelViewMatrix;",
        "uniform mat4 projectionMatrix;",
        "uniform mat4 viewMatrix;",
        "uniform mat4 normalMatrix;",
        ""
    };
    std::vector<std::string> prefixFragment = {
        //generatePrecision(props),
        "#define FRAGMENT_SHADER",
        props.HasVertexColor() ? "#define USE_COLOR" : "",
        "#define SHADER_NAME " + props.GetName() + "_fragment",
        ""
    };

    vertextShaderContent = resolveIncludes(vertextShaderContent);
    fragmentShaderContent = resolveIncludes(fragmentShaderContent);

    std::string vertexPrefixText = Utility::join(prefixVector.begin(), prefixVector.end(), "\n");
    std::string fragmentPrefixText = Utility::join(prefixFragment.begin(), prefixFragment.end(), "\n");

    const std::string fullVertexShader = versionString + vertexPrefixText + vertextShaderContent;
    const std::string fullFragmentShader = versionString + fragmentPrefixText + fragmentShaderContent;

    DEBUG("--------------------------------------------------");
    DEBUG(fullVertexShader);
    DEBUG("--------------------------------------------------");
    DEBUG(fullFragmentShader);
    DEBUG("--------------------------------------------------");


    createProgram(fullVertexShader, fullFragmentShader);

    updateUniforms();
    updateAttributes();
}

Uniforms& Program::GetUniforms() {
    return _uniforms;
}

const ProgramAttributes& Program::GetAttributes() {
    return _attributes;
}

void Program::Use() {
    GL_CHECK2(glUseProgram, _id);
}
