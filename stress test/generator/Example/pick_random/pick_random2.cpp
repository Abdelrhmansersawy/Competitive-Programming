#include <iostream>
#include <vector>

#include "../../random_generator_lib.h"

int main()
{

    std::vector<std::pair<int, long long>> v_p = {
        {1, (long long)1e18},
        {25, (long long)1e10},
        {1, 9},
        {5000, 5000000000},
    };

    std::pair<int, long long> pick1 = pick_random(v_p);
    std::pair<int, long long> pick2 = pick_random(v_p);
    std::cout << pick1.first << " " << pick1.second << "\n";
    std::cout << pick2.first << " " << pick2.second << "\n";

    return 0;
}