#include <iostream>

#include "../random_generator_lib.h" 


int main() {
    std::vector<std::vector<long long>> mat = random_matrix(3, 3, 100, 200);

    int row = mat.size(), col = mat[0].size();

    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
}