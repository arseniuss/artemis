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

#ifndef OPENGL_CAPABILITIES_HPP
#define OPENGL_CAPABILITIES_HPP

namespace OpenGL {
    class Capabilities {
    private:
        int _maxTextures;
        int _maxVertexTextures;
        int _maxTextureSize;
        int _maxCubemapSize;
        int _maxAttributes;
        int _maxVertexUniform;
        int _maxVarying;
        int _maxFragmentUnifoms;
    public:
        Capabilities();
    };
}

#endif /* !OPENGL_CAPABILITIES_HPP */
