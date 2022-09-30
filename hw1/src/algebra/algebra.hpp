#pragma once
#ifndef ALGEBRA_H_
#define ALGEBRA_H_

#include <cstddef>

#include "matrix.hpp"

namespace algebra
{
    template <typename T>
    Matrix2d<T> eye(std::size_t n);
} // namespace algebra

#endif // ALGEBRA_H_