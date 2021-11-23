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

#ifndef UTILITY_BOXMULLER_HPP
#define UTILITY_BOXMULLER_HPP

#include <glm/exponential.hpp>
#include <glm/ext/scalar_constants.hpp>

#include <Utility/Random.hpp>
#include <glm/trigonometric.hpp>

namespace Utility {

    template<typename _RealType = float>
    class BoxMuller {
        static_assert(std::is_floating_point<_RealType>::value,
                "result_type must be a floating point type");
    public:
        typedef _RealType result_type;
    private:
        result_type _stddev;
        result_type _mean;
    public:

        BoxMuller(result_type stddev, result_type mean) : _stddev(stddev), _mean(mean) {

        }

        template<typename _RndRetType>
        result_type operator()(BaseRandom<_RndRetType>& rnd) {

            auto u1 = ((result_type) rnd() - (result_type) rnd.min()) / ((result_type) rnd.max() - (result_type) rnd.min());
            auto u2 = ((result_type) rnd() - (result_type) rnd.min()) / ((result_type) rnd.max() - (result_type) rnd.min());

            auto x1 = glm::sqrt(-2.0f * glm::log(u1));
            auto x2 = 2.0f * glm::pi<result_type>() * u2;
            auto z1 = x1 * glm::sin(x2);

            return z1 * _stddev + _mean;
        }
    };
}

#endif /* !UTILITY_BOXMULLER_HPP */
