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

    template <typename T>
    Matrix2d<T> zeros(std::size_t n)
    {
        return Matrix2d<T>(n, n, 0);
    }

    template <typename T>
    Matrix2d<T> zeros(std::size_t n, std::size_t m)
    {
        return Matrix2d<T>(n, m, 0);
    }

    template <typename T>
    void swapRows(Matrix2d<T> &matrix, std::size_t r1, std::size_t r2)
    {
        std::valarray<T> row1 = matrix.row(r1);
        std::valarray<T> row2 = matrix.row(r2);
        matrix.row(r1) = row2;
        matrix.row(r2) = row1;
    }

    template Matrix2d<double> eye(std::size_t);
    template Matrix2d<double> zeros(std::size_t);
    template Matrix2d<double> zeros(std::size_t, std::size_t);
    template void swapRows(Matrix2d<double> &matrix, std::size_t r1, std::size_t r2);
} // namespace algebra
