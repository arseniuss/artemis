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

#include <Common/Debug.hpp>
#include <Galaxy/SphereGalaxyGenerator.hpp>

using namespace Galaxy;

SphereGalaxyGenerator::SphereGalaxyGenerator(size_t sz, float densityDev, float densityMean, glm::vec3 deviation) {
    _isGenerated = false;
    _size = sz;

    _densityDeviation = densityDev;
    _densityMean = densityMean;
    _deviation = deviation;
    
    Common::Debug() << "size=" << _size 
            << " densityDeviation=" << _densityDeviation 
            << " densituMean=" << _densityMean
            << " deviation=[" << _deviation.x << "," << _deviation.y << "," << _deviation.z << "]"
            << std::endl;
}

std::vector<Star>& SphereGalaxyGenerator::Generate(Utility::Random& random) {
    if (!_isGenerated) {
        std::normal_distribution<double> nd(_densityMean, _densityDeviation);
        auto density = std::max(0.0, (double)nd(random));
        auto countMax = std::max(0.0, _size * _size * _size * density);

        std::uniform_int_distribution<> uid(0, countMax);

        auto count = uid(random);

        Common::Debug() << "Generating " << count << " stars [0 .. " << countMax << "]" << std::endl;

        std::normal_distribution<double> xnd(0, _deviation.x * _size);
        std::normal_distribution<double> ynd(0, _deviation.y * _size);
        std::normal_distribution<double> znd(0, _deviation.z * _size);

        for (int i = 0; i < count; i++) {
            glm::vec3 pos;

            pos.x = xnd(random);
            pos.y = ynd(random);
            pos.z = znd(random);

            auto d = pos.length() / _size;
            auto m = d * 2000 + (1 - d) * 150000;

            std::normal_distribution<double> tnd(m, 4000);

            auto t = tnd(random);

            //Common::Debug() << "Star[" << pos.x << "," << pos.y << "," << pos.z << "] temp=" << t << std::endl;

            _stars.push_back(Star(pos, "", t));
        }

        _isGenerated = true;
        Common::Debug() << "Done" << std::endl;
    }

    return _stars;
}

