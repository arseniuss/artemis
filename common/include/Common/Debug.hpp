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

#ifdef NDEBUG
#define DEBUG(x)
#define DEBUG_ONCE(x)
#else
#define DEBUG(x)            std::cout << x << std::endl;
#define DEBUG_ONCE(x)       ({static bool sent = false; if(!sent) { std::cout << x << std::endl; sent = true; }})
#endif

#endif /* !COMMON_DEBUG_HPP */
