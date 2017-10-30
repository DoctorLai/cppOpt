/*
    Copyright (c) 2017 Martin Buck
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation the rights to
    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
    and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef OPTALGORITHMBASE_H
#define OPTALGORITHMBASE_H

#include "IOptAlgorithm.h"

namespace cppOpt
{

using namespace std;

template <typename T>
class OptAlgorithmBase : public IOptAlgorithm<T>
{
public:
    virtual OptCalculation<T> get_next_calculation(
        vector<OptCalculation<T>> const& previous,
        OptCalculation<T>         const* best,
        OptBoundaries<T>          const& boundaries) = 0; ///@todo rename?
protected:
    static T random_factor()
    {
        return rand()/(T)(RAND_MAX);
    }

//------------------------------------------------------------------------------

    static OptCalculation<T> random_calculation(OptBoundaries<T> const& boundaries)
    {
        OptCalculation<T> optCalculation;
        for(auto const& boundary : boundaries)
        {
            T newValue = boundary.second.min + random_factor() * boundary.second.range();
            optCalculation.add_parameter(boundary.second.name, newValue);
        }
        return optCalculation;
    }

//------------------------------------------------------------------------------

    static T calculate_random_change(const OptBoundary<T> &boundary, T temperature)
    {
        T change, maxChange;

        maxChange = (T)0.5 * boundary.range() * temperature;
        change = random_factor() * maxChange;

        if(rand() % 2)
            change *= -1.0;

        return change;
    }

//------------------------------------------------------------------------------

    static bool valid(const OptCalculation<T> &optCalculation, OptBoundaries<T> const& boundaries)
    {
        for(auto const& boundary : boundaries)
        {
            if(   optCalculation.get_parameter(boundary.first) < boundary.second.min
               || optCalculation.get_parameter(boundary.first) > boundary.second.max)
               return false;
        }
        return true;
    }
};

} // namespace cppOpt

#endif // OPTALGORITHMBASE_H