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

#include <Utility/Random.hpp>

using namespace Utility;

Random::Random(uint32_t seed) {
    if (!seed) _seed = ~seed;
}

Random::result_type Random::get(int x) {
    return get(x, _seed);
}

Random::result_type Random::get(int x, Random::result_type seedOvrd) {
    constexpr uint32_t bitNoise1 = 0x68e31da4;
    constexpr uint32_t bitNoise2 = 0xb5297a4d;
    constexpr uint32_t bitNoise3 = 0x1b56c4e9;

    uint32_t mangled = static_cast<uint32_t> (x);

    mangled *= bitNoise1;
    mangled += seedOvrd;
    mangled ^= (mangled >> 8);
    mangled *= bitNoise2;
    mangled ^= (mangled << 8);
    mangled *= bitNoise3;
    mangled ^= (mangled >> 8);

    return mangled;
}

Random::result_type Random::next() {
    static int counter = 0;

    return get(counter++);
}
