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
#include <regex>
#include <vector>

#include <OpenGL/Program.hpp>
#include <Common/Debug.hpp>

#include "glad.h"

using namespace OpenGL;

std::map<unsigned int, std::string> shaderExtensions = {
    {GL_VERTEX_SHADER, "vert"},
    {GL_FRAGMENT_SHADER, "frag"},
    {GL_GEOMETRY_SHADER, "geom"}
};

Program::Program() {

}

std::string Program::generatePrecision(const Common::Dictionary& parameters) {
    std::string precision = parameters.GetString("precision");
    std::string str = "precision " + precision + "float;\nprecision " + precision + " int;";

    if (precision == "highp") {
        str += "\n#define HIGH_PRECISION";
    } else if (precision == "mediump") {
        str += "\n#define MEDIUM_PRECISION";
    } else if (precision == "lowp") {
        str += "\n#define LOW_PRECISION";
    }

    return str;
}

std::string Program::resolveIncludes(std::string& text) {
    static std::regex pattern("^[ \\t]*#include +<(.*)>$");
    
    return text;
}


void Program::Build(const Common::Dictionary& parameters) {
    std::vector<std::string> prefixVector = {
        generatePrecision(parameters),
        ("#define SHADER_NAME " + parameters.GetString("shaderName"))
    };
    std::vector<std::string> prefixFragment = {
        generatePrecision(parameters),
        ("#define SHADER_NAME " + parameters.GetString("shaderName"))
    };


}


