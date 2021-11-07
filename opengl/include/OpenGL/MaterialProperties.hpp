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

#ifndef OPENGL_MATERIALPROPERTIES_HPP
#define OPENGL_MATERIALPROPERTIES_HPP

#include <memory>
#include <string>

#include "glad.h"

namespace OpenGL {
    class Program;

    class MaterialProperties {
    private:
        int _version = 0;

        std::string _precision;

        std::string _name;
        std::string _glslVersion = "330 core";

        std::string _vertexShaderText;
        std::string _fragmentShaderText;

        bool _hasVertexColors = false;

        std::shared_ptr<Program> _program;

        std::string loadShader(GLenum type);
    public:
        MaterialProperties(const std::string& materialName, const std::string& objectName);

        const std::string& GetPrecision() const;

        std::shared_ptr<Program> GetProgram();

        void SetProgram(std::shared_ptr<Program> program) {
            _program = program;
        }

        int GetVersion() const {
            return _version;
        }

        void SetVersion(int version) {
            _version = version;
        }

        const std::string& GetName() const {
            return _name;
        }

        std::string GetGLSLVersion() const {
            return _glslVersion;
        }

        const std::string& GetVertextShaderText() const {
            return _vertexShaderText;
        }

        const std::string& GetFragmentShaderText() const {
            return _fragmentShaderText;
        }

        bool HasVertexColor() const {
            return _hasVertexColors;
        }
    };
}

#endif /* !OPENGL_MATERIALPROPERTIES_HPP */
