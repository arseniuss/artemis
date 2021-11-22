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

#include <Common/Config.hpp>
#include <OpenGL/MaterialProperties.hpp>
#include <Utility/Filesystem.hpp>

#include "glad.h"

using namespace OpenGL;

std::map<unsigned int, std::string> shaderExtensions = {
    {GL_VERTEX_SHADER, "_vert.glsl"},
    {GL_FRAGMENT_SHADER, "_frag.glsl"},
    {GL_GEOMETRY_SHADER, "_geom.glsl"}
};

MaterialProperties::MaterialProperties() {

}

template <typename T>
void loadOptional(Common::Config& config, const std::string& section, const std::string& name, T& prop) {
    if (config.Exists(section, name)) {
        prop = config.Get<T>(section, name, T());
    } else {
        config.Set<T>(section, name, prop);
    }
}

void MaterialProperties::Load(const std::string& name) {
    std::string filename = "data/props/" + name + ".yaml";

    if (!std::filesystem::exists(filename))
        throw std::runtime_error("Material properties " + filename + " do not exist!");

    Common::Config config(filename);

    loadOptional(config, "material", "name", _name);
    loadOptional(config, "material", "precision", _precision);

    loadOptional(config, "material", "vertex colors", _vertexColors);
    loadOptional(config, "material", "vertex alphas", _vertexAlphas);
    loadOptional(config, "material", "vertex UVs", _vertexUVs);

    loadOptional(config, "material", "GLSL version", _glslVersion);
    loadOptional(config, "material", "shader name", _shaderName);

    config.Save();

    std::string shaderFilename = "data/shaders/" + _name;

    _vertexShaderText = Utility::LoadFullFile(shaderFilename + shaderExtensions[GL_VERTEX_SHADER]);
    _fragmentShaderText = Utility::LoadFullFile(shaderFilename + shaderExtensions[GL_FRAGMENT_SHADER]);
}

int MaterialProperties::GetVersion() const {
    return _version;
}

void MaterialProperties::SetVersion(int version) {
    _version = version;
}

const std::string& MaterialProperties::GetName() const {
    return _name;
}

const std::string& MaterialProperties::GetPrecision() const {
    return _precision;
}

std::shared_ptr<Program> MaterialProperties::GetProgram() {
    return _program;
}

void MaterialProperties::SetProgram(std::shared_ptr<Program> program) {
    _program = program;
}

const std::string& MaterialProperties::GetVertextShaderText() const {
    return _vertexShaderText;
}

const std::string& MaterialProperties::GetFragmentShaderText() const {
    return _fragmentShaderText;
}
