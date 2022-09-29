#pragma once
#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <array>
#include <string>

#include <cctype>
#include <cstddef>


namespace utils
{
    using Vectord = std::vector<double>;
    using Matrixd = std::vector<Vectord>;

    bool isNumber(char *arg);

    template <typename T>
    T strto(char *value);

    Matrixd getData(const std::string path);
    Matrixd generateDesignMatrix(const Matrixd &points, const std::size_t numberOfBases);
}

#endif // UTILS_H_