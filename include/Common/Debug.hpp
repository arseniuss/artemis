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

#ifndef COMMON_DEBUG_HPP
#define COMMON_DEBUG_HPP

#include <iostream>

namespace Common {
    typedef std::ostream& (*str_fn)(std::ostream&);

    class Log {
    public:

        Log(std::ostream& o);

        template<typename T>
        Log& operator<<(T t) {

            _output << t;

            return *this;
        }

        Log& operator<<(str_fn func);
    private:
        std::ostream& _output;
    };

    class Debug : public Log {
    public:

        Debug();
    };

    class Error : public Log {
    public:

        Error();
    };
}

#endif /* !COMMON_DEBUG_HPP */

