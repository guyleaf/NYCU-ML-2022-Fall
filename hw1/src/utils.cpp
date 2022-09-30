#include "utils.h"

#include <ostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stdexcept>

#include <cstddef>
#include <cmath>
#include <cassert>

namespace utils
{
    bool isNumber(char *arg)
    {
        bool state = true;
        while (state && *arg != '\0')
        {
            state = isdigit(*arg) || *arg == '.';
            arg++;
        }
        return state;
    }

    template <typename T>
    T strto(char *value)
    {
        std::istringstream iss(value);
        T target;
        iss >> target;
        assert(!iss.fail());

        return target;
    }
    template std::size_t strto<std::size_t>(char *);
    template double strto<double>(char *);

    template <typename T>
    void printMatrix(std::ostream &os, const algebra::Matrix2d<T> &matrix)
    {
        for (const T &value : matrix)
        {
            os << value << " ";
        }
        os << std::endl;
    }
    template void printMatrix<double>(std::ostream &, const algebra::Matrix2d<double> &);

    Matrixd getData(const std::string path)
    {
        std::ifstream ifs(path, std::ifstream::in);
        if (!ifs.is_open())
        {
            throw std::runtime_error("The file " + path + " cannot be opened.");
        }

        Matrixd points;
        std::string point, x, y;
        while (ifs.good())
        {
            std::getline(ifs, point);
            std::istringstream iss(point);
            std::getline(iss, x, ',');
            std::getline(iss, y, ',');

            assert(!iss.fail());
            points.push_back(std::vector<double>{std::stod(x), std::stod(y)});
        }
        return points;
    }

    Matrixd generateDesignMatrix(const Matrixd &points, const std::size_t numberOfBases)
    {
        Matrixd matrix;
        for (auto point : points)
        {
            Vectord row;
            for (auto power = numberOfBases; power > 0; power--)
            {
                row.push_back(std::pow(point[0], power - 1));
            }
            matrix.push_back(row);
        }
        return matrix;
    }
} // namespace utils