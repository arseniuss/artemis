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
#include <Common/Observer.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/Materials/BasicMeshMaterial.hpp>
#include <Graphics/Materials/CustomMaterial.hpp>
#include <Graphics/Materials/PointsMaterial.hpp>
#include <OpenGL/MaterialProperties.hpp>
#include <Utility/Filesystem.hpp>
#include <Utility/String.hpp>

#include "glad.h"
#include "Graphics/Materials/MeshMaterial.hpp"

using namespace OpenGL;

std::map<unsigned int, std::string> shaderExtensions = {
    {GL_VERTEX_SHADER, "_vert.glsl"},
    {GL_FRAGMENT_SHADER, "_frag.glsl"},
    {GL_GEOMETRY_SHADER, "_geom.glsl"}
};

MaterialPropertyMap MaterialProperties::_properties;

std::shared_ptr<MaterialProperties> MaterialProperties::GetOrEmpty(std::shared_ptr<Graphics::Material> mat) {
    auto it = _properties.find(mat->weak_from_this());

    if (it != _properties.end())
        return it->second;

    auto props = std::make_shared<MaterialProperties>();

    _properties.emplace(mat->weak_from_this(), props);
    Common::RegisterOnDestruct<Graphics::Material>(mat, [](auto a) {
        MaterialProperties::Remove(a);
    });

    return props;
}

void MaterialProperties::Remove(std::weak_ptr<Graphics::Material> mat) {
    _properties.erase(mat);
}

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

void MaterialProperties::Update(std::shared_ptr<Graphics::Material> mat) {
    size_t h = mat->GetHash();

    if (h == Graphics::CustomMaterial::Hash) {

    } else {
        _name = mat->GetTypeName();
        _shaderName = Utility::Replace(mat->GetTypeName(), ' ', '_');

        if (h == Graphics::MeshMaterial::Hash) {
            auto m = std::static_pointer_cast<Graphics::MeshMaterial>(mat);
            
            _uniformColor = false;
            _vertexColors = true;
        } else if (h == Graphics::BasicMeshMaterial::Hash) {
            auto m = std::static_pointer_cast<Graphics::BasicMeshMaterial>(mat);

            _uniformColor = true;
            if (_uniformColor) _colorAlphas = true;
        } else if (h == Graphics::PointsMaterial::Hash) {
            auto m = std::static_pointer_cast<Graphics::PointsMaterial>(mat);

            _vertexColors = true;
        } else {
            throw std::runtime_error("Unrecognised material " + mat->GetTypeName());
        }
    }

    std::string shaderFilename = "data/shaders/" + _shaderName;

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

const std::string& MaterialProperties::GetShaderName() const {
    return _shaderName;
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

bool MaterialProperties::HasUniformColor() const {
    return _uniformColor;
}

void MaterialProperties::HasUniformColor(bool value) {
    _uniformColor = value;
}

bool MaterialProperties::HasColorAphas() const {
    return _colorAlphas;
}

bool MaterialProperties::HasVertexColor() const {
    return _vertexColors;
}

