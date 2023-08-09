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
        str[i] = 'a' + random32(0, 26);

    return str;
}

/**
 * @brief pick random item fron vector of items
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
 * @brief pick random item fron vector of items then remove it from the vector
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
    std::vector<int> nodes_of_depth[height + 1];
    std::vector<int> nodes(number_of_nodes);
    iota(nodes.begin(), nodes.end(), 1);
    std::shuffle(nodes.begin(), nodes.end(), random_seed);

    nodes_of_depth[0] = {root};
    for (int h = 1; h <= height; ++h)
    {
        int random_node = pick_random_and_remove(nodes);
        if (random_node == root)
        {
            --h;
            continue;
        }

        if (edges.empty())
            edges.push_back({root, random_node});
        else
            edges.push_back({edges.back().second, random_node});

        nodes_of_depth[h].emplace_back(random_node);
    }

    while (!nodes.empty())
    {
        int random_not_connected_node = pick_random_and_remove(nodes);
        if (random_not_connected_node == root)
            continue;

        int random_depth = random32(0, height - 1);
        int random_connected_node = pick_random(nodes_of_depth[random_depth]);

        edges.push_back({random_connected_node, random_not_connected_node});
        nodes_of_depth[random_depth + 1].push_back(random_not_connected_node);
    }

    std::shuffle(edges.begin(), edges.end(), random_seed);

    return edges;
}