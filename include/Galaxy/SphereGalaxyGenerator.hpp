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

#ifndef GALAXY_SPHEREGALAXYGENERATOR_HPP
#define GALAXY_SPHEREGALAXYGENERATOR_HPP

#include <Galaxy/GalaxyGenerator.hpp>

namespace Galaxy {

    class SphereGalaxyGenerator : public GalaxyGenerator {
    private:
        size_t _size;
        float _densityDeviation;
        float _densityMean;
        glm::vec3 _deviation;

        std::vector<Star> _stars;
    protected:
        bool _isGenerated;
    public:
        SphereGalaxyGenerator(size_t sz, float densityDev = 0.0000025f, float densityMean = 0.000001f,
                glm::vec3 deviation = glm::vec3{0.0000025f});

        std::vector<Star>& Generate(std::knuth_b& random) override;

    };

}

#endif /* GALAXY_SPHEREGALAXYGENERATOR_HPP */
