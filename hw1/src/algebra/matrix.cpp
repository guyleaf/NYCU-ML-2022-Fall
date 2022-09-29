#include "matrix.hpp"

#include <cassert>
#include <stdexcept>

namespace algebra
{
    // define constructors
    template <typename T>
    Matrix2d<T>::Matrix2d(std::size_t rows, const std::valarray<T> &data) : _rows(rows), _cols(data.size() / rows), _data(data)
    {
        assert((_rows * _cols) == _data.size());
    }

    template <typename T>
    Matrix2d<T>::Matrix2d(std::size_t rows, std::size_t cols) : _rows(rows), _cols(cols), _data(std::valarray<T>(rows * cols))
    {
    }

    template <typename T>
    Matrix2d<T>::Matrix2d(std::size_t rows, std::size_t cols, const T &value) : _rows(rows), _cols(cols), _data(std::valarray<T>(value, rows * cols))
    {
    }

    // define operators
    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator+=(const Matrix2d<T> &lhs)
    {
        this->_data += lhs._data;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator+=(const T &lhs)
    {
        this->_data += lhs;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator-=(const Matrix2d<T> &lhs)
    {
        this->_data -= lhs._data;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator-=(const T &lhs)
    {
        this->_data -= lhs;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator*=(const Matrix2d<T> &lhs)
    {
        // TODO: matrix multiplication
        this->_data -= lhs._data;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator*=(const T &lhs)
    {
        this->_data *= lhs;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator/=(const Matrix2d<T> &lhs)
    {
        // TODO: matrix division (apply & multiply)
        throw std::runtime_error("The division operation of matrix2d is not yet implemented.");
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator/=(const T &lhs)
    {
        this->_data /= lhs;
        return *this;
    }

    template class Matrix2d<double>;
}