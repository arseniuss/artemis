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

#include <Common/Debug.hpp>

#include "glad.h"
#include "OpenGL/Capabilities.hpp"

using namespace OpenGL;

Capabilities::Capabilities() {
    GLint range[2] = {0, 0};
    GLint precision;

    glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_HIGH_FLOAT, range, &precision);
    Common::Debug() << "VERTEX_SHADER HIGH_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision << std::endl;

    glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_MEDIUM_FLOAT, range, &precision);
    Common::Debug() << "VERTEX_SHADER MEDIUM_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision << std::endl;

    glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_LOW_FLOAT, range, &precision);
    Common::Debug() << "VERTEX_SHADER LOW_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision << std::endl;

    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_HIGH_FLOAT, range, &precision);
    Common::Debug() << "FRAGMENT_SHADER HIGH_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision << std::endl;

    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_MEDIUM_FLOAT, range, &precision);
    Common::Debug() << "FRAGMENT_SHADER MEDIUM_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision << std::endl;

    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_LOW_FLOAT, range, &precision);
    Common::Debug() << "FRAGMENT_SHADER LOW_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision << std::endl;

    GLint tmp;

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &tmp);
    Common::Debug() << "MAX_TEXTURE_IMAGE_UNITS = " << tmp << std::endl;
    _maxTextures = tmp;

    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &tmp);
    Common::Debug() << "MAX_VERTEX_TEXTURE_IMAGE_UNITS = " << tmp << std::endl;
    _maxVertexTextures = tmp;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &tmp);
    Common::Debug() << "MAX_TEXTURE_SIZE = " << tmp << std::endl;
    _maxTextureSize = tmp;

    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &tmp);
    Common::Debug() << "MAX_CUBE_MAP_TEXTURE_SIZE = " << tmp << std::endl;
    _maxCubemapSize = tmp;

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &tmp);
    Common::Debug() << "MAX_VERTEX_ATTRIBS = " << tmp << std::endl;
    _maxAttributes = tmp;

    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &tmp);
    Common::Debug() << "MAX_VERTEX_UNIFORM_VECTORS = " << tmp << std::endl;
    _maxVertexUniform = tmp;

    glGetIntegerv(GL_MAX_VARYING_VECTORS, &tmp);
    Common::Debug() << "MAX_VARYING_VECTORS = " << tmp << std::endl;
    _maxVarying = tmp;

    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &tmp);
    Common::Debug() << "MAX_FRAGMENT_UNIFORM_VECTORS = " << tmp << std::endl;
    _maxFragmentUnifoms = tmp;
}

static bool isPrecisionOK(GLenum precisionType) {
    bool ok = true;
    GLint precision;

    glGetShaderPrecisionFormat(GL_VERTEX_SHADER, precisionType, nullptr, &precision);
    ok &= precision > 0;
    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, precisionType, nullptr, &precision);
    ok &= precision > 0;

    return ok;
}

std::string Capabilities::VerifyPrecision(std::string precision) const {
    if (precision == "highp") {
        if (isPrecisionOK(GL_HIGH_FLOAT)) {
            return "highp";
        }
        precision = "mediump";
    }

    if (precision == "mediump") {
        if (isPrecisionOK(GL_MEDIUM_FLOAT)) {
            return "mediump";
        }
    }

    return "lowp";
}

