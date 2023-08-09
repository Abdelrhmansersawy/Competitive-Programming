#include <iostream>
#include <vector>

#include "../../random_generator_lib.h"

void print(std::vector<int> &v)
{
    std::cout << "current vector:\n";
    for (int &x : v)
        std::cout << x << " ";
    std::cout << "\n";
}

int main()
{

    std::vector<int> v = {4, 5, 6, 1};
    print(v);

    std::cout << "picked: " << pick_random_and_remove(v) << "\n";
    print(v);
    std::cout << "picked: " << pick_random_and_remove(v) << "\n";
    print(v);

    return 0;
}