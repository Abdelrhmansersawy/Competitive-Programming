#include <iostream>

#include "../random_generator_lib.h"

int main()
{
    std::vector<int> vec = random_permutation(1000);
    for (auto element : vec)
        std::cout << element << " ";
    std::cout << std::endl;
    return 0;
}