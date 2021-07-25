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

namespace OpenGL {
    class Program {
    protected:
        unsigned int _id;
        
        unsigned int load(unsigned int type, const std::string& filename);
        
        std::string generatePrecision(const Common::Dictionary& parameters);
        std::string resolveIncludes(std::string& text);
    public:
        Program();
        
        void Build(const Common::Dictionary& parameters);
    };
}

#endif /* !OPENGL_PROGRAM_HPP */
