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

#include <complex>

#include <Common/Random.hpp>

using namespace Common;

RangeRandomComponent::RangeRandomComponent(double min, double max) : _min(min), _max(max) {

}

double RangeRandomComponent::Compute(double v) {
    return v * (_max - _min) + _min;
}

std::pair<double, double> RangeRandomComponent::Compute(std::pair<double, double> v) {
    return {
        v.first * (_max - _min) + _min,
        v.second * (_max - _min) + _min};
}

BoxMullerRandomComponent::BoxMullerRandomComponent(double stdDeviation, double mean) : _stdDeviation(stdDeviation),
_mean(mean) {

}

double BoxMullerRandomComponent::Compute(double v) {
    throw std::runtime_error("Cannot compute from one value");
}

std::pair<double, double> BoxMullerRandomComponent::Compute(std::pair<double, double> v) {
    auto x1 = sqrt(-2.0 * log(v.first));
    auto x2 = 2.0 * M_PI * v.second;
    auto z1 = x1 * sin(x2);
    auto z2 = x1 * cos(x2);

    return {z1, z2};
}

uint64_t Random::value(const void* data, size_t sz) {
    return XXH64(data, sz, _seed);
}

Random::Random(uint64_t seed) : _data(nullptr), _len(0), _seed(seed), _counter(0) {

}

Random::~Random() {
    free(_data);
}

double Random::Value() {
    uint64_t result;

    if (_data != nullptr) {
        result = value(_data, _len);
    } else {
        result = value(&_counter, sizeof (_counter++));
    }

    double v = result / (double) UINT64_MAX;

    for (auto c : _components) {
        v = c->Compute(v);
    }

    return v;
}

std::pair<double, double> Random::Values() {
    std::pair<double, double> result;

    if (_data != nullptr) {
        result = {
            value(_data, _len) / (double) UINT64_MAX,
            value(_data, _len) / (double) UINT64_MAX
        };
    } else {
        result = {
            value(&_counter, sizeof (_counter++)) / (double) UINT64_MAX,
            value(&_counter, sizeof (_counter++)) / (double) UINT64_MAX
        };
    }

    for (auto c : _components) {
        result = c->Compute(result);
    }

    return result;
}

Random& Random::Range(double min, double max) {
    _components.push_back(std::make_shared<RangeRandomComponent>(min, max));

    return *this;
}

Random& Random::At(int a) {
    _len = sizeof (int);
    _data = malloc(_len);
    *(int *) _data = a;

    return *this;
}
