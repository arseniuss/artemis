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

#include <random>
#include <functional>

#include <Common/Debug.hpp>
#include <Galaxy/SphereGalaxyGenerator.hpp>
#include <Utility/BoxMuller.hpp>

using namespace Galaxy;

SphereGalaxyGenerator::SphereGalaxyGenerator(size_t sz, float densityDev, float densityMean, glm::vec3 deviation) {
    _isGenerated = false;
    _size = sz;

    _densityDeviation = densityDev;
    _densityMean = densityMean;
    _deviation = deviation;

    DEBUG("size=" << _size
            << " densityDeviation=" << _densityDeviation
            << " densityMean=" << _densityMean
            << " deviation=[" << _deviation << "]");
}

std::vector<Star>& SphereGalaxyGenerator::Generate(Utility::Random& random) {
    if (!_isGenerated) {
        Utility::BoxMuller<float> bm(_densityDeviation, _densityMean);
        auto density = std::max(0.0f, bm(random));
        auto countMax = std::max<float>(0.0f, _size * _size * _size * density);

        std::uniform_int_distribution<> uid(0, countMax);

        auto count = uid(random);

        Utility::BoxMuller<float> xnd(_deviation.x * _size, 0);
        Utility::BoxMuller<float> ynd(_deviation.y * _size, 0);
        Utility::BoxMuller<float> znd(_deviation.z * _size, 0);

        DEBUG("Generating " << count << " stars [0 .. " << countMax << "]");
        DEBUG("Density " << density);

        for (int i = 0; i < count; i++) {
            glm::vec3 pos;

            pos.x = xnd(random);
            pos.y = ynd(random);
            pos.z = znd(random);

            auto d = (float) pos.length() / (float) _size;
            float m = d * 2000.0f + (1.0f - d) * 15000.0f;

            std::normal_distribution<float> tnd(m, 40000.0f);

            auto t = tnd(random);

            //DEBUG("Star[" << pos.x << "," << pos.y << "," << pos.z << "] temp=" << t);

            _stars.push_back(Star(pos, "", t));
        }

        _isGenerated = true;
        DEBUG("Done");
    }

    return _stars;
}

