#include <iostream>

#include "../random_generator_lib.h"

int main()
{

    std::cout << random64(1, (long long)1e18) << "\n";
    std::cout << random64(1, (long long)1e18) << "\n";
    std::cout << random64(1, (long long)1e18) << "\n";
    std::cout << random64(1, (long long)1e18) << "\n";
    std::cout << random64(1, (long long)1e18) << "\n";

    return 0;
}