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
#ifndef COMMON_RANDOM_HPP
#define COMMON_RANDOM_HPP

#include <xxhash.h>
#include <vector>
#include <memory>

namespace Common {

    class RandomComponent {
    public:
        virtual double Compute(double v) = 0;
        virtual std::pair<double, double> Compute(std::pair<double, double> v) = 0;
    };

    class RangeRandomComponent : public RandomComponent {
        double _min;
        double _max;
    public:

        RangeRandomComponent(double min, double max);

        double Compute(double v) override;
        std::pair<double, double> Compute(std::pair<double, double> v) override;
    };

    class BoxMullerRandomComponent : public RandomComponent {
        double _stdDeviation;
        double _mean;
    public:

        BoxMullerRandomComponent(double stdDeviation, double mean);
        
        double Compute(double v) override;
        std::pair<double, double> Compute(std::pair<double, double> v) override;
    };

    class Random {
    private:
        std::vector<std::shared_ptr<RandomComponent>> _components;

        void *_data;
        size_t _len;
        uint64_t _seed;
        uint64_t _counter;
    protected:

        uint64_t value(const void *data, size_t sz);
    public:

        Random(uint64_t seed);

        ~Random();

        double Value();

        std::pair<double, double> Values();

        Random& Range(double min, double max);

        Random& At(int a);


    };
}

#endif /* !COMMON_RANDOM_HPP */
