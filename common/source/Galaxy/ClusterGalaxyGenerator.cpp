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

#include <Common/Debug.hpp>
#include <Galaxy/ClusterGalaxyGenerator.hpp>

using namespace Galaxy;

ClusterGalaxyGenerator::ClusterGalaxyGenerator(GalaxyGenerator& gen,
        float countMean, float countDeviation, glm::vec3 deviation) :
_gen(gen) {
    _countMean = countMean;
    _countDeviation = countDeviation;
    _deviation = deviation;
}

std::vector<Star>& ClusterGalaxyGenerator::Generate(Utility::Random& random) {
    auto& stars = _gen.Generate(random);

    if (!_generated) {
        std::normal_distribution<double> nd(_countMean, _countDeviation);
        auto count = nd(random);

        std::normal_distribution<double> xnd(0, _deviation.x);
        std::normal_distribution<double> ynd(0, _deviation.y);
        std::normal_distribution<double> znd(0, _deviation.z);

        for (size_t i = 0; i < count; i++) {
            glm::vec3 center;

            center.x = xnd(random);
            center.y = ynd(random);
            center.z = znd(random);

            for(size_t i = 0; i < stars.size(); i++) {
                stars[i].position += center;
            }
        }

        _generated = true;
    }

    return stars;
}

