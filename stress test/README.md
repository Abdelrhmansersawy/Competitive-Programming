# Generators
## Random seeds
```c++
mt19937 random_seed(time(0));
```
## Random number 
```c++
long long rnd(long long l , long long r){
    if(l > r) throw invalid_argument("parameters is invalid");
    uniform_int_distribution<long long> dist(l, r);
    return dist(random_seed);
}
```
## Random pick
```c++
template <typename T>
T pick_random(vector<T> &vec){
    if (vec.empty())
        throw invalid_argument("can not pick from empty vector");

    int index = rnd(0, vec.size() - 1);
    return vec[index];
}

```
## Pick random and remove
```c++
template <typename T>
T pick_random_and_remove(vector<T> &vec){
    if (vec.empty())
        throw invalid_argument("can not pick from empty vector");

    int index = rnd(0, vec.size() - 1);
    swap(vec[index], vec.back());
    T value = vec.back();
    vec.pop_back();

    return value;
}

```

## Random Tree
```c++
// random tree
vector<pair<int, int>> random_tree(int number_of_nodes = -1, int root = -1, int height = -1){
    if (!~number_of_nodes)
        number_of_nodes = rnd(1, 100000);

    if (number_of_nodes <= 1)
        return {};

    // pick random root if not given or given and not valid
    if (root > number_of_nodes or root < 1)
        root = rnd(1, number_of_nodes);

    // pick random height if not given
    if (!~height)
        height = rnd(1, number_of_nodes - 1);
    // if height is too small set it to 1
    if (height < 1)
        height = 1;
    // if height is too tall set it to max
    if (height > number_of_nodes - 1)
        height = number_of_nodes - 1;

    vector<pair<int, int>> edges;
    int depth[number_of_nodes];
    vector<int> nodes_to_connect, disconnected_nodes(number_of_nodes);
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

    shuffle(edges.begin(), edges.end(), random_seed);
    return edges;
}

```
## Random DAG
```c++
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rnd(){return rng();} 
// The maximum number of vertices for the random graph, number of edges
const int maxVertex = 10  , e = 4;

// Function to check for a cycle upon addition of a new edge in the graph
bool checkAcyclic(vector<vector<int>>& edge, int ed, vector<bool>& check, int v) {
    bool value;
    // If the current vertex is visited already, then the graph contains a cycle
    if (check[v] == true)
        return false;
    else {
        check[v] = true;
        // For each vertex, go for all the vertices connected to it
        for (int i = ed; i >= 0; i--) {
            if (edge[i][0] == v)
                return checkAcyclic(edge, ed, check, edge[i][1]);
        }
    }
    // In case the path ends then reassign the vertices visited in that path to false again
    check[v] = false;
    if (ed == 0)
        return true;
    return true;
}

// Function to generate a random graph
void generateRandomGraphs() {
    int count;
    vector<vector<int>> edge(e, vector<int>(2));
    vector<bool> check(21, false);


    // Build a connection between two random vertices
    int i = 0, j = 0;
    while (i < e) {
        edge[i][0] = rnd() % maxVertex + 1;
        edge[i][1] = rnd() % maxVertex + 1;

        for (j = 1; j <= maxVertex; j++)
            check[j] = false;

        if (checkAcyclic(edge, i, check, edge[i][0]) == true)
            i++;
    }
    vector<pair<int,int>> v;

    for (i = 0; i < maxVertex; i++) {
        count = 0;
        for (j = 0; j < e; j++) {
            if (edge[j][0] == i + 1) {
                v.emplace_back(edge[j][0] , edge[j][1]);
                count++;
            }        }
    }
    cout << maxVertex << " " << v.size() << '\n';
    for(auto &[x,y] : v) cout << x << " " << y << '\n';
}

int main() {
    generateRandomGraphs();
    return 0;
}
```
***
# Bash Script for Stress test
## 1. Using Diff
## Generator
```sh
path=$1
mkdir $path
cd $path
touch {brute,code,gen}.cpp
touch {correctAnswer,input_file,myAnswer}
touch script.sh
open script.sh
```
## Stress test
```sh
set -e
g++ code.cpp -o code
g++ gen.cpp -o gen
g++ brute.cpp -o brute
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
    diff -Z myAnswer correctAnswer > /dev/null || break
    echo "Passed test: "  $i
done
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer
```
## 2. Using Custom checker
## Generator
```sh
path=$1
mkdir $path
cd $path
touch {brute,code,gen,checker}.cpp
touch {correctAnswer,input_file,myAnswer,checker_log}
touch script.sh
open script.sh
```
## Stress test
```sh
set -e
g++ code.cpp -o code
g++ gen.cpp -o gen
g++ brute.cpp -o brute
g++ checker.cpp -o checker
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
    ./checker > checker_log
    echo "Passed test: "  $i
done
```
## Custom checker
```c++
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

int readAns(ifstream &fin){
    // check that output
}
int main(int argc, char * argv[]){
    ifstream fin("input_file", ifstream::in);
    ifstream ans("myAnswer", ifstream::in);
    ifstream cor("correctAnswer", ifstream::in);
    // read the test case using "fin"
    int myAnswer = readAns(ans);
    int correctAnswer = readAns(cor);
    // Compare two myAnswer and correctAnswer and return "-1" if you fail in this testcase. 
    
    return 0;
}
```
