#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>

std::vector<std::array<int, 2>> getData(std::string path) {
    return std::vector<std::array<int, 2>>{};
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        throw std::invalid_argument("The arguments should be textfile path, polynomial bases, lambda (LSE).");
    }
    return 0;
}