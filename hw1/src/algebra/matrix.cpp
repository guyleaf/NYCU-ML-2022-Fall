#include "matrix.hpp"

#include <string>
#include <cassert>
#include <stdexcept>

namespace algebra
{
    const std::string NOT_DIVISIBLE_SIZE_MSG = "The size of data is not divisible by rows.";
    const std::string ZERO_SIZE_MSG = "Invalid rows and cols value.";
    const std::string NOT_SAME_SIZE_MSG = "The size of two matrices are not equal.";
    const std::string NOT_MULTIPLIABLE_MSG = "The size of cols of the first matrix is not equal to the size of rows of the second matrix.";

    // define constructors
    template <typename T>
    Matrix2d<T>::Matrix2d(std::size_t rows, const std::valarray<T> &data) : _rows(rows), _cols(data.size() / rows), _data(data)
    {
        if ((_rows * _cols) != _data.size())
        {
            throw std::runtime_error(NOT_DIVISIBLE_SIZE_MSG);
        }
    }

    template <typename T>
    Matrix2d<T>::Matrix2d(std::size_t rows, std::size_t cols, const std::valarray<T> &data) : _rows(rows), _cols(cols), _data(data)
    {
        if ((_rows * _cols) != _data.size())
        {
            throw std::runtime_error(NOT_DIVISIBLE_SIZE_MSG);
        }
    }

    template <typename T>
    Matrix2d<T>::Matrix2d(std::size_t rows, std::size_t cols) : _rows(rows), _cols(cols), _data(std::valarray<T>(rows * cols))
    {
        if (rows * cols == 0)
        {
            throw std::runtime_error(ZERO_SIZE_MSG);
        }
    }

    template <typename T>
    Matrix2d<T>::Matrix2d(std::size_t rows, std::size_t cols, const T &value) : _rows(rows), _cols(cols), _data(std::valarray<T>(value, rows * cols))
    {
        if (rows * cols == 0)
        {
            throw std::runtime_error(ZERO_SIZE_MSG);
        }
    }

    // define public functions
    template <typename T>
    std::valarray<T> Matrix2d<T>::row(std::size_t r) const
    {
        return this->_data[std::slice(r * this->_cols, this->_cols, 1)];
    }

    template <typename T>
    std::slice_array<T> Matrix2d<T>::row(std::size_t r)
    {
        return this->_data[std::slice(r * this->_cols, this->_cols, 1)];
    }

    template <typename T>
    std::valarray<T> Matrix2d<T>::col(std::size_t c) const
    {
        return this->_data[std::slice(c, this->_rows, this->_cols)];
    }

    template <typename T>
    std::slice_array<T> Matrix2d<T>::col(std::size_t c)
    {
        return this->_data[std::slice(c, this->_rows, this->_cols)];
    }

    template <typename T>
    Matrix2d<T> Matrix2d<T>::transpose() const
    {
        Matrix2d<T> result(this->_cols, this->_rows);
        for (std::size_t i = 0; i < result._rows; i++)
        {
            result.row(i) = this->col(i);
        }
        return result;
    }

    template <typename T>
    Matrix2d<T> Matrix2d<T>::inverse() const
    {
        Matrix2d<T> result(this->_cols, this->_rows);
        // for (std::size_t i = 0; i < result._rows; i++)
        // {
        //     result[i] = this->col(i);
        // }
        return result;
    }

    // define operators
    template <typename T>
    const T &Matrix2d<T>::operator()(std::size_t r, std::size_t c) const
    {
        return this->_data[r * this->_cols + c];
    }

    template <typename T>
    T &Matrix2d<T>::operator()(std::size_t r, std::size_t c)
    {
        return this->_data[r * this->_cols + c];
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator+=(const Matrix2d<T> &rhs)
    {
        if (this->_rows != rhs._rows || this->_cols != rhs._cols)
        {
            throw std::runtime_error(NOT_SAME_SIZE_MSG);
        }

        this->_data += rhs._data;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator+=(const T &rhs)
    {
        this->_data += rhs;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator-=(const Matrix2d<T> &rhs)
    {
        if (this->_rows != rhs._rows || this->_cols != rhs._cols)
        {
            throw std::runtime_error(NOT_SAME_SIZE_MSG);
        }

        this->_data -= rhs._data;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator-=(const T &rhs)
    {
        this->_data -= rhs;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator*=(const Matrix2d<T> &rhs)
    {
        if (this->_cols != rhs._rows)
        {
            throw std::runtime_error(NOT_MULTIPLIABLE_MSG);
        }

        std::valarray<T> result(this->_rows * rhs._cols);
        for (std::size_t i = 0; i < rhs._cols; i++)
        {
            for (std::size_t j = 0; j < this->_rows; j++)
            {
                std::valarray<T> &&tmp = std::valarray<T>(this->row(j)) * rhs.col(i);
                result[j * rhs._cols + i] = tmp.sum();
            }
        }
        this->_data = result;
        this->_cols = rhs._cols;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator*=(const T &rhs)
    {
        this->_data *= rhs;
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator/=(const Matrix2d<T> &rhs)
    {
        if (this->_cols != rhs._rows)
        {
            throw std::runtime_error(NOT_MULTIPLIABLE_MSG);
        }

        (*this) *= Matrix2d<T>(rhs._rows, (1 / rhs._data));
        return *this;
    }

    template <typename T>
    Matrix2d<T> &Matrix2d<T>::operator/=(const T &rhs)
    {
        this->_data /= rhs;
        return *this;
    }

    template <typename T>
    bool Matrix2d<T>::operator==(const Matrix2d<T> &rhs) const
    {
        return (this->_data == rhs._data).min();
    }

    template <typename T>
    bool Matrix2d<T>::operator!=(const Matrix2d<T> &rhs) const
    {
        return !(*this == rhs);
    }

    #undef DEFINE_BINARY_OPERATOR
    #define DEFINE_BINARY_OPERATOR(_Op)  \
        template <typename T>   \
        Matrix2d<T> operator _Op(const Matrix2d<T> &lhs, const Matrix2d<T> &rhs)    \
        {   \
            Matrix2d<T> result(lhs);    \
            result _Op##= rhs;  \
            return result;  \
        }   \
            \
        template <typename T>   \
        Matrix2d<T> operator _Op(const typename Matrix2d<T>::value_type &lhs, const Matrix2d<T> &rhs)   \
        {   \
            Matrix2d<T> result(rhs);    \
            result _Op##= lhs;  \
            return result;  \
        }   \
            \
        template <typename T>   \
        Matrix2d<T> operator _Op(const Matrix2d<T> &lhs, const typename Matrix2d<T>::value_type &rhs)   \
        {   \
            Matrix2d<T> result(lhs);    \
            result _Op##= rhs;  \
            return result;  \
        }

    DEFINE_BINARY_OPERATOR(+)
    DEFINE_BINARY_OPERATOR(-)
    DEFINE_BINARY_OPERATOR(*)
    DEFINE_BINARY_OPERATOR(/)

    template class Matrix2d<double>;
}