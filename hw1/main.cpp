#include <iostream>

#include <string>
#include <stdexcept>

#include "regression.hpp"
#include "utils.hpp"


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
    int numberOfbases = std::stoi(argv[2]);
    double lambda = std::stof(argv[3]);

    auto points = utils::getData(filePath);

    return 0;
}