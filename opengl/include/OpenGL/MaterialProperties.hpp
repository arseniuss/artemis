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

namespace Graphics {
    class Material;
    class BufferGeometry;
}

namespace OpenGL {
    class Program;
    class MaterialProperties;

    using MaterialPropertyMap = std::map<std::weak_ptr<Graphics::Material>,
            std::shared_ptr<MaterialProperties>, std::owner_less<>>;

    class MaterialProperties {
    private:
        static MaterialPropertyMap _properties;

        int _version = 0;

        std::string _name;
        std::string _precision = "highp";

        bool _instancing = false;
        bool _instancedColor = false;

        bool _vertexColors = false;
        bool _colorAlphas = false;
        bool _vertexUVs = false;

        bool _uniformColor = false;
        
        bool _hasTexture = false;

        std::string _shaderName;

        std::string _vertexShaderText;
        std::string _fragmentShaderText;

        std::shared_ptr<Program> _program;
    public:
        static std::shared_ptr<MaterialProperties> GetOrEmpty(std::shared_ptr<Graphics::Material> mat);
        static void Remove(std::weak_ptr<Graphics::Material> mat);

        MaterialProperties();

        void Update(std::shared_ptr<Graphics::Material> mat, std::shared_ptr<Graphics::BufferGeometry> geo);

        int GetVersion() const;
        void SetVersion(int version);

        const std::string& GetName() const;
        const std::string& GetShaderName() const;

        const std::string& GetPrecision() const;

        std::shared_ptr<Program> GetProgram();
        void SetProgram(std::shared_ptr<Program> program);

        const std::string& GetVertextShaderText() const;

        const std::string& GetFragmentShaderText() const;

        bool HasVertexColor() const;
        bool HasUniformColor() const;
        void HasUniformColor(bool value);
        bool HasColorAphas() const;
        bool HasVertexUVs() const;
        
        bool HasTexture() const;
    };
}

#endif /* !OPENGL_MATERIALPROPERTIES_HPP */
