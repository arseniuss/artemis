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

#include <filesystem>
#include <fstream>
#include <map>

#include <OpenGL/MaterialProperties.hpp>
#include <Utility/Filesystem.hpp>

#include "glad.h"

using namespace OpenGL;

std::map<unsigned int, std::string> shaderExtensions = {
    {GL_VERTEX_SHADER, "_vert.glsl"},
    {GL_FRAGMENT_SHADER, "_frag.glsl"},
    {GL_GEOMETRY_SHADER, "_geom.glsl"}
};

MaterialProperties::MaterialProperties(const std::string& materialName, const std::string& objectName) : _name(materialName) {
    // TODO: load 
    _vertexShaderText = Utility::LoadFullFile("data/shaders/" + objectName + shaderExtensions[GL_VERTEX_SHADER]);
    _fragmentShaderText = Utility::LoadFullFile("data/shaders/" + objectName + shaderExtensions[GL_FRAGMENT_SHADER]);
}

const std::string& MaterialProperties::GetPrecision() const {
    return _precision;
}

std::shared_ptr<Program> MaterialProperties::GetProgram() {
    return _program;
}
