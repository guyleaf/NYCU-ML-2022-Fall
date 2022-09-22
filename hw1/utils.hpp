#pragma once
#include <fstream>
#include <sstream>

#include <vector>
#include <array>
#include <utility>
#include <string>
#include <cctype>
#include <stdexcept>

namespace utils
{
    using Vectord = std::vector<double>;
    using Matrix2d = std::vector<std::pair<double, double>>;

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

    Matrix2d getData(const std::string path)
    {
        std::ifstream ifs(path, std::ifstream::in);
        if (!ifs.is_open())
        {
            throw std::runtime_error("The file " + path + " cannot be opened.");
        }

        Matrix2d points;
        std::string point, x, y;
        while (ifs.good())
        {
            std::getline(ifs, point);
            std::stringstream ss(point);
            std::getline(ss, x, ',');
            std::getline(ss, y, ',');

            points.push_back(std::make_pair(std::stod(x), (std::stod(y))));
        }
        return points;
    }
} // namespace utils
