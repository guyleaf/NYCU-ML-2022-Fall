#pragma once
#ifndef MATRIX2D_H_
#define MATRIX2D_H_

#include <valarray>
#include <cstddef>

namespace algebra
{
    template <typename T>
    class Matrix2d
    {
        using value_type = T;

    public:
        // creates based on the rows and data size
        explicit Matrix2d(std::size_t rows, const std::valarray<T>& data);
        // creates an empty n x m matrix
        explicit Matrix2d(std::size_t rows, std::size_t cols);
        // creates an n x m matrix initialized with value
        explicit Matrix2d(std::size_t rows, std::size_t cols, const value_type &value);

        // get the number of rows in the matrix2d
        std::size_t rows() const;
        // get the number of columns in the matrix2d
        std::size_t cols() const;
        // get a copy of the data in the matrix2d
        std::valarray<value_type> array() const;

        // retrieve the data from row r of the matrix
        std::valarray<value_type> row(std::size_t r) const;
        // retrieve the data from col c of the matrix
        std::valarray<value_type> col(std::size_t c) const;
        // retrieve refernce to the data from row r of the matrix
        std::slice_array<value_type> row(std::size_t r);
        // retrieve refernce to the data from col c of the matrix
        std::slice_array<value_type> col(std::size_t c);

        // basic item reference
        value_type &operator()(std::size_t r, std::size_t c);
        // basic item retrieval
        const value_type &operator()(std::size_t r, std::size_t c) const;

        // genetate a new matrix that is the transposition of this one
        Matrix2d<value_type> transpose();

        Matrix2d<value_type> &operator+=(const Matrix2d<value_type> &lhs);
        Matrix2d<value_type> &operator+=(const value_type &lhs);

        Matrix2d<value_type> &operator-=(const Matrix2d<value_type> &lhs);
        Matrix2d<value_type> &operator-=(const value_type &lhs);

        Matrix2d<value_type> &operator*=(const Matrix2d<value_type> &lhs);
        Matrix2d<value_type> &operator*=(const value_type &lhs);

        Matrix2d<value_type> &operator/=(const Matrix2d<value_type> &lhs);
        Matrix2d<value_type> &operator/=(const value_type &lhs);

    private:
        std::size_t _rows, _cols;
        std::valarray<value_type> _data;
    };
} // namespace algebra

#endif // MATRIX2D_H_