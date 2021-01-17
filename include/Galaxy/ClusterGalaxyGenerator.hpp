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

#ifndef GALAXY_CLUSTERGALAXYGENERATOR_HPP
#define GALAXY_CLUSTERGALAXYGENERATOR_HPP

#include <Galaxy/GalaxyGenerator.hpp>

namespace Galaxy {

    class ClusterGalaxyGenerator : public GalaxyGenerator {
    protected:
        std::vector<Star> _stars;
    public:

        std::vector<Star>& Generate() override {
            return _stars;
        }
    };
}

#endif /* !GALAXY_CLUSTERGALAXYGENERATOR_HPP */
