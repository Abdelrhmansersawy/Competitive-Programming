#include "random_generator_lib.h"

/**
 * @brief generate random integer(int)
 *
 * @param low, high the generated number will be in range [low, high] inclusive
 * @return int
 */
int random32(int low, int high)
{
    if (low > high)
        throw std::invalid_argument("random32 parameters is invalid");
    std::uniform_int_distribution<int> dist(low, high);
    return dist(random_seed);
}

/**
 * @brief generate random integer(long long)
 *
 * @param low, high the generated number will be in range [low, high] inclusive
 * @return long long
 */
long long random64(long long low, long long high)
{
    if (low > high)
        throw std::invalid_argument("random64 parameters is invalid");

    std::uniform_int_distribution<long long> dist(low, high);
    return dist(random_seed);
}

/**
 * @brief generate random number of (length) digit in O(length)
 *
 * @param length
 * @return std::string
 */
std::string random_huge_number(int length)
{
    std::string str(length, ' ');
    for (int i = 0; i < length; ++i)
        str[i] = '0' + random32(!i, 9);

    return str;
}

/**
 * @brief generate random string or lower case characters in O(length)
 *
 * @param length
 * @return std::string
 */
std::string random_string(int length)
{
    std::string str(length, ' ');
    for (int i = 0; i < length; ++i)
        str[i] = 'a' + random32(0, 25);

    return str;
}

/**
 * @brief pick random item from vector of items
 *
 * @tparam T the data type of vector
 * @param vec the container
 * @return T the data type of vector is same as the returned data type
 */
template <typename T>
T pick_random(std::vector<T> &vec)
{
    if (vec.empty())
        throw std::invalid_argument("can not pick from empty vector");

    int index = random32(0, vec.size() - 1);
    return vec[index];
}

/**
 * @brief pick random item from vector of items then remove it from the vector
 *
 * @tparam T the data type of vector
 * @param vec the container
 * @return T the data type of vector is same as the returned data type
 */
template <typename T>
T pick_random_and_remove(std::vector<T> &vec)
{
    if (vec.empty())
        throw std::invalid_argument("can not pick from empty vector");

    int index = random32(0, vec.size() - 1);
    std::swap(vec[index], vec.back());
    T value = vec.back();
    vec.pop_back();

    return value;
}

/**
 * @brief generates random tree in O(number_of_nodes)
 *
 * @param number_of_nodes
 * @param root optional paramater. if it is not given the root will be random node
 * @param height optional paramater. if it is not given it will be random
 * and if it was incorrect it will be set to the nearest valid height
 * @return std::vector<std::pair<int, int>>. every pair represents an edge in the tree means that
 * pair.first have direct edge to pair.second. the vector will have size = number of nodes - 1
 */
std::vector<std::pair<int, int>> random_tree(int number_of_nodes = -1, int root = -1, int height = -1)
{
    if (!~number_of_nodes)
        number_of_nodes = random32(1, 100000);

    if (number_of_nodes <= 1)
        return {};

    // pick random root if not given or given and not valid
    if (root > number_of_nodes or root < 1)
        root = random32(1, number_of_nodes);

    // pick random height if not given
    if (!~height)
        height = random32(1, number_of_nodes - 1);
    // if height is too small set it to 1
    if (height < 1)
        height = 1;
    // if height is too tall set it to max
    if (height > number_of_nodes - 1)
        height = number_of_nodes - 1;

    std::vector<std::pair<int, int>> edges;
    int depth[number_of_nodes];
    std::vector<int> nodes_to_connect, disconnected_nodes(number_of_nodes);
    iota(disconnected_nodes.begin(), disconnected_nodes.end(), 1);

    depth[root - 1] = 0;
    nodes_to_connect.emplace_back(root);
    for (int h = 1; h <= height; ++h)
    {
        int random_disconnected_node = pick_random_and_remove(disconnected_nodes);
        if (random_disconnected_node == root)
        {
            --h;
            continue;
        }

        if (edges.empty())
        {
            depth[random_disconnected_node - 1] = 1 + depth[root - 1];
            edges.push_back({root, random_disconnected_node});
        }
        else
        {
            depth[random_disconnected_node - 1] = 1 + depth[edges.back().second - 1];
            edges.push_back({edges.back().second, random_disconnected_node});
        }

        if (depth[random_disconnected_node - 1] != height)
            nodes_to_connect.emplace_back(random_disconnected_node);
    }

    while (!disconnected_nodes.empty())
    {
        int random_disconnected_node = pick_random_and_remove(disconnected_nodes);
        if (random_disconnected_node == root)
            continue;
        int random_connected_node = pick_random(nodes_to_connect);

        depth[random_disconnected_node - 1] = 1 + depth[random_connected_node - 1];
        edges.push_back({random_connected_node, random_disconnected_node});

        if (depth[random_disconnected_node - 1] != height)
            nodes_to_connect.emplace_back(random_disconnected_node);
    }

    std::shuffle(edges.begin(), edges.end(), random_seed);

    return edges;
}

/**
 * @brief generates a random permutation in O(length)
 *
 * @param length
 * @return std::vector<int>
 */
std::vector<int> random_permutation(int length)
{
    if (length < 0)
        throw std::invalid_argument("can not generate negative size for permutation");

    std::vector<int> vec(length);
    std::iota(vec.begin(), vec.end(), 1);

    std::vector<int> randomized_vec;
    while (length--)
        randomized_vec.push_back(pick_random_and_remove(vec));

    return randomized_vec;
}

/**
 * @brief generates a random binary string in O(length)
 *
 * @param length
 * @return std::string
 */
std::string random_binary_string(int length)
{
    if (length < 0)
        throw std::invalid_argument("can not generate negative size for string");

    std::string str;
    while (length--)
        str.push_back('0' + random32(0, 1));

    return str;
}

/**
 * @brief return a random Boolean Value True/False in O(1)
 *
 * @return bool
 */

bool random_flag()
{
    return random32(0, 1);
}

/**
 * @brief returns a random vowel character
 *
 * @param isUpper optoinal(bool). In case not given or pass `false` function will return lower vowel character
 * otherwise function will return upper vowel character
 * @return char
 */

char random_vowel(bool isUpper=false)
{
    std::vector<char> vowels{'a', 'e', 'i', 'o', 'u'};
    char chosen = pick_random(vowels);
    return isUpper ? toupper(chosen) : chosen;
}

/**
 * @brief returns a matrix with 'row' rows and 'col' columns and the values in the matrix are in range [low, high]
 *
 * @param row - number of rows in the matrix
 * @param col - number of columns in the matrix
 * @param low - starting range
 * @param high - ending range
 * @return std::vector<std::vector<long long>>
 */

std::vector<std::vector<long long>> random_matrix(int row, int col, long long low, long long high)
{
    if (low > high)
    {
        throw std::invalid_argument("range is invalid");
    }
    if (row == 0 || col == 0)
    {
        throw std::invalid_argument("row or column can't be empty");
    }
    std::vector<std::vector<long long>> matrix(row, std::vector<long long>(col, 0));
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            matrix[i][j] = random64(low, high);
        }
    }
    return matrix;
}
