#include <iostream>

#include "../random_generator_lib.h"

int main()
{
    /*
        The dist(random_seed) expression generates a random integer using the distribution defined by the dist object, 
        and seeds the generator with the random_seed object. 
        The specific value that is generated will be a random integer within the range [low, high].
    */
    std::uniform_int_distribution<int> dist(1, 10);
    int rnd = dist(random_seed);
    std::cout << rnd << "\n";

    return 0;
}