#include <iostream>
#include <vector>

#include "../../random_generator_lib.h"

void print(std::vector<std::pair<int, long long>> &v)
{
    std::cout << "current vector:\n";
    for (std::pair<int, long long> &x : v)
        std::cout << x.first << " " << x.second << "\n";
    std::cout << "\n";
}

int main()
{

    std::vector<std::pair<int, long long>> v_p = {
        {1, (long long)1e18},
        {25, (long long)1e10},
        {1, 9},
        {5000, 5000000000},
    };
    print(v_p);

    std::pair<int, long long> pick1 = pick_random_and_remove(v_p);
    std::cout << "picked: " << pick1.first << " " << pick1.second << "\n";
    print(v_p);
    std::pair<int, long long> pick2 = pick_random_and_remove(v_p);
    std::cout << "picked: " << pick2.first << " " << pick2.second << "\n";
    print(v_p);

    return 0;
}