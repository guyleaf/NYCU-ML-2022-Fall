#include "utils.h"

#include <ostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <utility>
#include <stdexcept>

#include <cstddef>
#include <cmath>
#include <cassert>

#include "gnuplot-iostream.h"

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

    template <typename T>
    std::string describeLine(const algebra::Matrix2d<T> &params, bool gnuplot)
    {
        std::ostringstream oss;
        auto n = params.rows();
        for (auto i = params.rows(); i > 0; i--)
        {
            auto value = params(i - 1, 0);
            if (value >= 0 && i != n)
            {
                oss << " + ";
            }
            else if (value < 0)
            {
                oss << " - ";
            }
            oss << std::abs(value);
            if (i > 1)
            {
                if (gnuplot)
                {
                    oss << " * x ** " << i - 1;
                }
                else
                {
                    oss << "x^" << i - 1;
                }
            }
        }
        return oss.str();
    }
    template std::string describeLine<double>(const algebra::Matrix2d<double> &, bool);

    template <typename T>
    void plotLineAndPoints(std::string title, const algebra::Matrix2d<T> &params, const algebra::Matrix2d<T> &points)
    {
        Gnuplot gp;
        gp << "set border linewidth 1.5" << std::endl
           << "set style line 1 linecolor rgb 'red' linetype 1 linewidth 1" << std::endl
           << "set style line 2 linecolor rgb 'blue' linetype 7 pointsize 0.8" << std::endl
           << "set key box width 1 height 1 opaque" << std::endl
           << "set xrange [-100:100]" << std::endl
           << "set yrange [-10:500]" << std::endl
           << "set xlabel 'x'" << std::endl
           << "set ylabel 'y'" << std::endl
           << "set title '" << title << "'" << std::endl;

        gp << "f(x) = " << describeLine(params, true) << std::endl;
        gp << "plot f(x) with lines title 'f(x)' linestyle 1, "
           << "'-' with points title 'data' linestyle 2" << std::endl;

        gp.send1d(std::make_tuple(points.col(0), points.col(1)));
    }
    template void plotLineAndPoints<double>(std::string, const algebra::Matrix2d<double> &, const algebra::Matrix2d<double> &);

    algebra::Matrix2d<double> getData(const std::string path)
    {
        std::ifstream ifs(path, std::ifstream::in);
        if (!ifs.is_open())
        {
            throw std::runtime_error("The file " + path + " cannot be opened.");
        }

        std::vector<double> points;
        std::string point, x, y;
        while (ifs.good())
        {
            std::getline(ifs, point);
            std::istringstream iss(point);
            std::getline(iss, x, ',');
            std::getline(iss, y, ',');

            assert(!iss.fail());
            points.push_back(std::stod(x));
            points.push_back(std::stod(y));
        }
        return algebra::Matrix2d<double>(points.size() / 2, 2, points);
    }
} // namespace utils