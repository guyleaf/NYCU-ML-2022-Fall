#include <iostream>
#include <string>
#include <stdexcept>

#include <cmath>
#include <cstddef>

#include "algebra/algebra.hpp"
#include "utils.h"

algebra::Matrix2d<double> generateDesignMatrix(const algebra::Matrix2d<double> &points, const std::size_t numberOfBases)
{
    std::size_t n = points.rows();
    algebra::Matrix2d<double> matrix(n, numberOfBases);
    std::valarray<double> pointXColumn = points.col(0);
    for (std::size_t i = 0; i < n; i++)
    {
        double pointX = pointXColumn[i];
        for (std::size_t power = 0; power < numberOfBases; power++)
        {
            matrix(i, power) = std::pow(pointX, power);
        }
    }
    return matrix;
}

algebra::Matrix2d<double> fitPointsByrLSE(const algebra::Matrix2d<double> &a, const algebra::Matrix2d<double> &b, double lambda)
{
    auto transposedA = a.transpose();
    return (transposedA * a + algebra::eye<double>(a.cols(), lambda)).inverse() * transposedA * b;
}

algebra::Matrix2d<double> fitPointsByNewtonMethodWithLSE(const algebra::Matrix2d<double> &a, const algebra::Matrix2d<double> &b)
{
    auto transposedA = a.transpose();
    return (transposedA * a).inverse() * transposedA * b;
}

double calculateLSE(const algebra::Matrix2d<double> &a, const algebra::Matrix2d<double> &b, const algebra::Matrix2d<double> &w)
{
    return (a * w - b).pow(2).sum();
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

    std::cout.precision(10);

    std::string filePath(argv[1]);
    auto bases = utils::strto<std::size_t>(argv[2]);
    auto lambda = utils::strto<double>(argv[3]);

    auto points = utils::getData(filePath);
    auto a = generateDesignMatrix(points, bases);
    auto b = algebra::Matrix2d<double>(points.rows(), 1, points.col(1));

    auto weights = fitPointsByrLSE(a, b, lambda);
    std::cout << "LSE:" << std::endl;
    std::cout << "Fitting line: " << utils::describeLine(weights, false) << std::endl;
    std::cout << "Total Error: " << std::fixed << calculateLSE(a, b, weights) << std::endl;
    utils::plotLineAndPoints("rLSE (bases=" + std::to_string(bases) + ", lambda=" + std::to_string(lambda) + ")", weights, points);

    std::cout << std::endl;

    weights = fitPointsByNewtonMethodWithLSE(a, b);
    std::cout << "Newton's Method:" << std::endl;
    std::cout << "Fitting line: " << utils::describeLine(weights, false) << std::endl;
    std::cout << "Total Error: " << std::fixed << calculateLSE(a, b, weights) << std::endl;
    utils::plotLineAndPoints("Newton-Raphson method (bases=" + std::to_string(bases) + ")", weights, points);

    return 0;
}