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

        std::string _name;
        std::string _precision = "highp";
        
        bool _instancing = false;
        bool _instancedColor = false;
        
        bool _vertexColors = false;
        bool _vertexAlphas = false;
        bool _vertexUVs = false;
        
        std::string _glslVersion = "330 core";
        std::string _shaderName;

        std::string _vertexShaderText;
        std::string _fragmentShaderText;

        std::shared_ptr<Program> _program;
    public:
        MaterialProperties();

        void Load(const std::string& name);

        int GetVersion() const;
        void SetVersion(int version);

        const std::string& GetName() const;

        const std::string& GetPrecision() const;

        std::shared_ptr<Program> GetProgram();
        void SetProgram(std::shared_ptr<Program> program);

        std::string GetGLSLVersion() const {
            return _glslVersion;
        }

        const std::string& GetVertextShaderText() const;

        const std::string& GetFragmentShaderText() const;

        bool HasVertexColor() const {
            return _vertexColors;
        }
    };
}

#endif /* !OPENGL_MATERIALPROPERTIES_HPP */
