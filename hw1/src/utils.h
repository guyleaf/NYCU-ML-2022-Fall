#pragma once
#ifndef UTILS_H_
#define UTILS_H_

#include <string>

#include <cctype>
#include <cstddef>

#include "algebra/algebra.hpp"

namespace utils
{
    bool isNumber(char *arg);

    template <typename T>
    T strto(char *value);

    template <typename T>
    void printMatrix(std::ostream &os, const algebra::Matrix2d<T> &data);
    template <typename T>
    std::string describeLine(const algebra::Matrix2d<T> &params, bool gnuplot);

    template <typename T>
    void plotLineAndPoints(std::string, const algebra::Matrix2d<T> &params, const algebra::Matrix2d<T> &points);

    algebra::Matrix2d<double> getData(const std::string path);
}

#endif // UTILS_H_