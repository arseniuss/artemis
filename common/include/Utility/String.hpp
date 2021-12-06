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

#ifndef UTILITY_STRING_HPP
#define UTILITY_STRING_HPP

#include <string>

namespace Utility {

    using MatcherFunction = std::function<std::string(std::string, const std::vector<std::string>&)>;

    std::string Replace(std::string text, char from, char to);
    std::string RegexReplace(std::string text, std::string pattern, MatcherFunction matcher);

    std::string Demangle(const std::string& name);

    template<typename T>
    std::string join(T first, T last, const std::string delim = ",") {
        std::ostringstream res;

        if (first != last) {
            res << *first;
            while (++first != last) {
                res << delim << *first;
            }
        }

        return res.str();
    }

    template<typename T>
    std::string NameOf() {
        return Demangle(typeid (T).name());
    }
}

#endif /* !UTILITY_STRING_HPP */
