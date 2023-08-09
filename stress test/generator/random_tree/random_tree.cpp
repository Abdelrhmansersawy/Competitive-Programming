#include <iostream>
#include <vector>

#include "../../random_generator_lib.h"

int main()
{


    std::vector<std::pair<int, int>> edges = random_tree();

    for(std::pair<int, int>& edge: edges){
        std::cout << edge.first << " " << edge.second << "\n";
    }

    std::cout << "number of nodes: " << edges.size() + 1 << "\n";

    return 0;
}