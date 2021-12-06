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
#include <OpenGL/Capabilities.hpp>
#include <OpenGL/Debug.hpp>

#include "glad.h"

using namespace OpenGL;

Capabilities::Capabilities() {
    GLint range[2] = {0, 0};
    GLint precision;

    glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_HIGH_FLOAT, range, &precision);
    DEBUG("VERTEX_SHADER HIGH_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision);

    glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_MEDIUM_FLOAT, range, &precision);
    DEBUG("VERTEX_SHADER MEDIUM_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision);

    glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_LOW_FLOAT, range, &precision);
    DEBUG("VERTEX_SHADER LOW_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision);

    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_HIGH_FLOAT, range, &precision);
    DEBUG("FRAGMENT_SHADER HIGH_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision);

    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_MEDIUM_FLOAT, range, &precision);
    DEBUG("FRAGMENT_SHADER MEDIUM_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision);

    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_LOW_FLOAT, range, &precision);
    DEBUG("FRAGMENT_SHADER LOW_FLOAT range=[" << range[0] << ".." << range[1] << "] precision=" << precision);

    GLint tmp;

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &tmp);
    DEBUG("MAX_COMBINED_TEXTURE_IMAGE_UNITS = " << tmp);
    _maxCombinedTextures = tmp;

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &tmp);
    DEBUG("MAX_TEXTURE_IMAGE_UNITS = " << tmp);
    _maxTextures = tmp;

    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &tmp);
    DEBUG("MAX_VERTEX_TEXTURE_IMAGE_UNITS = " << tmp);
    _maxVertexTextures = tmp;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &tmp);
    DEBUG("MAX_TEXTURE_SIZE = " << tmp);
    _maxTextureSize = tmp;

    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &tmp);
    DEBUG("MAX_CUBE_MAP_TEXTURE_SIZE = " << tmp);
    _maxCubemapSize = tmp;

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &tmp);
    DEBUG("MAX_VERTEX_ATTRIBS = " << tmp);
    _maxAttributes = tmp;

    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &tmp);
    DEBUG("MAX_VERTEX_UNIFORM_VECTORS = " << tmp);
    _maxVertexUniform = tmp;

    glGetIntegerv(GL_MAX_VARYING_VECTORS, &tmp);
    DEBUG("MAX_VARYING_VECTORS = " << tmp);
    _maxVarying = tmp;

    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &tmp);
    DEBUG("MAX_FRAGMENT_UNIFORM_VECTORS = " << tmp);
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

int Capabilities::GetMaxCombinedTextures() const {
    return _maxCombinedTextures;
}

int Capabilities::GetMaxTextures() const {
    return _maxTextures;
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

