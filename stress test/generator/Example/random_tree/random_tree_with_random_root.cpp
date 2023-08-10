#include <iostream>
#include <vector>

#include "../../random_generator_lib.h"

int main()
{

    int number_of_nodes = 13;

    std::vector<std::pair<int, int>> edges = random_tree(number_of_nodes);

    for(std::pair<int, int>& edge: edges){
        std::cout << edge.first << " " << edge.second << "\n";
    }

    return 0;
}