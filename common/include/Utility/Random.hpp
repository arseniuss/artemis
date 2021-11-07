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

#ifndef UTILITY_RANDOM_HPP
#define UTILITY_RANDOM_HPP

#include <cstdint>

namespace Utility {

    class Random {
    private:
        uint32_t _seed;
    public:
        typedef uint32_t result_type;
        
        Random(uint32_t seed);
        
        result_type get(int x);
        result_type get(int x, Random::result_type seedOvrd);
        
        result_type operator()() {
            return next();
        }

        result_type min() {
            return 0;
        }

        result_type max() {
            return UINT32_MAX;
        }

        result_type next();
    };
}

#endif /* !UTILITY_RANDOM_HPP */
