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

#ifndef GALAXY_GALAXYGENERATOR_HPP
#define GALAXY_GALAXYGENERATOR_HPP

#include <random>

#include <Galaxy/Star.hpp>
#include <Utility/Random.hpp>

namespace Galaxy {

    class GalaxyGenerator {
    public:
        virtual std::vector<Star>& Generate(Utility::Random& random) = 0;
    };
}

#endif /* !GALAXY_GALAXYGENERATOR_HPP */
