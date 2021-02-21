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
        bool _generated;

        GalaxyGenerator& _gen;
        float _countMean;
        float _countDeviation;
        glm::vec3 _deviation;
    public:
        ClusterGalaxyGenerator(GalaxyGenerator& gen,
                float countMean = 0.0000025f, float countDeviation = 0.000001f,
                glm::vec3 deviation = glm::vec3{0.0000025f});

        std::vector<Star>& Generate(std::knuth_b& random) override;
    };
}

#endif /* !GALAXY_CLUSTERGALAXYGENERATOR_HPP */
