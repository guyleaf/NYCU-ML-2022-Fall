﻿#include "algebra/algebra.hpp"
#include "utils.h"

#include <iostream>

#include <string>
#include <stdexcept>
#include <cstddef>

utils::Vectord fitPointsByrLSE(utils::Matrixd points, int numberOfBases, double lambda)
{
    return {};
}

utils::Vectord fitPointsByNewtonMethodWithLSE(utils::Matrixd points, int numberOfBases)
{
    return {};
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        throw std::invalid_argument("The arguments should be textfile path, polynomial bases, lambda (LSE).");
    }
    if (!utils::isNumber(argv[2]))
    {
        throw std::invalid_argument("The arguments polynomial bases must be a number.");
    }
    if (!utils::isNumber(argv[3]))
    {
        throw std::invalid_argument("The arguments lambda (LSE) must be a number.");
    }

    std::string filePath(argv[1]);
    auto numberOfbases = utils::strto<std::size_t>(argv[2]);
    auto lambda = utils::strto<double>(argv[3]);

    auto points = utils::getData(filePath);

    algebra::Matrix2d<double> a(3, 5, 0.2), b(4, 5, 0.1);

    a += b;

    return 0;
}