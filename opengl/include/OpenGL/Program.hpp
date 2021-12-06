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

#ifndef OPENGL_PROGRAM_HPP
#define OPENGL_PROGRAM_HPP

#include <string>

#include <Common/Dictionary.hpp>
#include <OpenGL/MaterialProperties.hpp>
#include <OpenGL/Uniforms.hpp>

#include "glad.h"

namespace Graphics {
    class Material;
}

namespace OpenGL {

    struct ProgramAttribute {
        int location;
        size_t type_hash;
    };

    using ProgramAttributes = std::map<std::string, ProgramAttribute>;

    class Program : public std::enable_shared_from_this<Program> {
    protected:
        unsigned int _id;
        Uniforms _uniforms;
        ProgramAttributes _attributes;

        unsigned int load(unsigned int type, const std::string& filename);

        std::string generatePrecision(const MaterialProperties& parameters);
        std::string resolveIncludes(std::string& prefix, std::string& text);

        GLuint compilerShader(GLenum shader_type, const std::string& source);
        void createProgram(const std::string& vertexSource, const std::string& fragmentSource);

        void updateAttributes();
        void updateUniforms();
    public:
        static std::shared_ptr<Program> Find(std::weak_ptr<Graphics::Material> material);

        Program();
        ~Program();

        void Build(std::shared_ptr<MaterialProperties> props);

        Uniforms& GetUniforms();
        const ProgramAttributes& GetAttributes();

        void Use();
    };
}

#endif /* !OPENGL_PROGRAM_HPP */
