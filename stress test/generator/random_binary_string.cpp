#include <iostream>

#include "../random_generator_lib.h"

int main()
{
    std::string str = random_binary_string(1000);
    std::cout << str << std::endl;

    return 0;
}