#include "algebra.hpp"

#include <valarray>

namespace algebra
{
    template <typename T>
    Matrix2d<T> eye(std::size_t n)
    {
        Matrix2d<T> result(n, n, 0);
        for (std::size_t i = 0; i < n; i++)
        {
            result(i, i) = 1;
        }
        return result;
    }
    template Matrix2d<double> eye(std::size_t);
} // namespace algebra
