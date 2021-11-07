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

#include <fstream>
#include <sstream>
#include <filesystem>

#include <Utility/Filesystem.hpp>


namespace Utility {

    std::string LoadFullFile(const std::string& filepath) {

        if (!std::filesystem::exists(filepath)) {
            throw std::runtime_error("File " + filepath + " do not exist!");
        }

        std::ifstream in;
        std::stringstream ss;

        in.open(filepath);
        ss << in.rdbuf();
        in.close();

        return ss.str();
    }
}