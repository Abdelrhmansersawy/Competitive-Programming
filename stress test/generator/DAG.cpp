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
