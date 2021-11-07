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

#include <regex>

#include <Common/Debug.hpp>
#include <Utility/String.hpp>

using namespace Utility;

std::string Utility::RegexReplace(std::string text, std::string pattern, MatcherFunction matcher) {
    std::regex r(pattern);
    std::smatch matches;

    std::string ret = "";
    std::string suffix;

    while (std::regex_search(text, matches, r)) {
        std::vector<std::string> mat;

        for (size_t i = 0; i < matches.size(); i++) {
            mat.emplace_back(matches[i]);
        }

        ret += std::string(matches.prefix()) + matcher(matches[0], mat);
        suffix = text = matches.suffix();
    }

    ret += suffix;

    return ret;
}
