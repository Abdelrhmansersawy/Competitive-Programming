#include <iostream>
#include <vector>

#include "../../random_generator_lib.h"

int main()
{

    std::vector<int> v = {4, 5, 6, 1};
    std::cout << pick_random(v) << "\n";
    std::cout << pick_random(v) << "\n";

    return 0;
}