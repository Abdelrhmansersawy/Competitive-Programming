# Competitive Programming Library

A comprehensive collection of algorithms and data structures commonly used in competitive programming.

Here's a last updated handbook version [Serso Library](Handbook%20material/Serso%20Library.pdf)

----

## Table of Contents

1. [Data Structures](#data-structures)
2. [Dynamic Programming](#dynamic-programming)
3. [Graph Algorithms](#graph-algorithms)
4. [Mathematics](#mathematics)
5. [String Algorithms](#string-algorithms)
6. [Tree Algorithms](#tree-algorithms)
7. [Code Snippets](#code-snippets)
8. [Handbook material](#handbook-material)
9. [How to contribute](#contributing)

## Data Structures

### Range Queries
- [2D Prefix Sum](Data%20Structure/2D%20Range%20Queries/2D_prefixsum.cpp)
- [2D Sparse Table](Data%20Structure/2D%20Range%20Queries/2d_sparsetable.cpp)
- [3D Prefix Sum](Data%20Structure/2D%20Range%20Queries/3D_prefixsum.cpp)
- [BIT 2D](Data%20Structure/2D%20Range%20Queries/BIT2D.cpp)
- [Segment Tree 2D](Data%20Structure/2D%20Range%20Queries/segTree_2d.cpp)

### Advanced Data Structures
- [Binary Indexed Tree (BIT)](Data%20Structure/BIT/BIT.cpp)
- [BIT with Lazy Propagation](Data%20Structure/BIT/BIT_LAZY_MODIFICATION.cpp)
- [BIT with Coordinate Compression](Data%20Structure/BIT/BIT_with_coordinate_compression.cpp)
- [DSU](Data%20Structure/DSU/DSU.cpp)
- [Rollback DSU](Data%20Structure/DSU/RollbackUF.cpp)
- [DSU on Trees](Data%20Structure/DSU%20on%20tree/small_to_large_trick.cpp)
- [KD-tree 3D](Data%20Structure/Kd-tree/kd-tree%203d.cpp)
- [LCA](Data%20Structure/LCA/LCA.cpp)
- [LCA in DSU](Data%20Structure/LCA/LCA_in_DSU.cpp)
- [LCA O(1)](Data%20Structure/LCA/lca_O(1).cpp)

### Specialized Structures
- [Monotonic Queue](Data%20Structure/Montomic%20stack%20and%20Queue/monotonicQueue.cpp)
- [Next/Previous Min/Max](Data%20Structure/Montomic%20stack%20and%20Queue/NxtorPrv_MinorMax.cpp)
- [Ordered Set](Data%20Structure/Ordered%20set/ordered_set.cpp)
- [Persistent Segment Tree](Data%20Structure/Persistent%20Segment%20tree/PersistentSegmentTree_pointer.cpp)
- [Mo's Algorithm](Data%20Structure/SQRT%20and%20Mo's/MO-Algorithm.cpp)
- [Treap](Data%20Structure/Treap/Treap.cpp)
- [Xor Basis](Data%20Structure/Xor%20Basis/xor_basis_application.cpp)

## Dynamic Programming

### Optimization Techniques
- [Convex Hull Trick Max](DP/Convex%20Hull/CHT_maxline.cpp)
- [Convex Hull Trick Min](DP/Convex%20Hull/CHT_minline.cpp)
- [Divide and Conquer DP](DP/Divide%20and%20Conquer/DP_dnc.cpp)
- [Knuth's Optimization](DP/Knuth's/DP_knuths_cpAlgo.cpp)

### Common Problems
- [Knapsack with Bitset](DP/Knapsack/knapsack_with_bitset.cpp)
- [Sum over Subsets](DP/Sum%20of%20subset/SOS_DP.cpp)
- [Largest Zero Submatrix](DP/Zero%20matrix/largest_zero_submatrix.cpp)

## Graph Algorithms

### Basic Algorithms
- [0-1 BFS](Graph/01_BFS.cpp)
- [BFS](Graph/BFS.cpp)
- [Dijkstra](Graph/dijkstra.cpp)
- [Dijkstra for Sparse Graphs](Graph/dijkstra_sparse_graph.cpp)
- [Floyd Warshall](Graph/floyd.cpp)
- [Bellman Ford](Graph/bellman_ford.cpp)

### Graph Properties
- [Articulation Points](Graph/artPoints.cpp)
- [Bridges](Graph/Bridges.cpp)
- [Biconnected Components](Graph/biConnected.cpp)
- [Strongly Connected Components (Kosaraju)](Graph/SCC_kosaraju.cpp)
- [Strongly Connected Components (Tarjan)](Graph/SCC_tarjan.cpp)

### Special Paths
- [Euler Circuit (Undirected)](Graph/euler_ciruite_undirectedgraph.cpp)
- [Euler Path (Directed)](Graph/euler_path_directed.cpp)
- [K-th Shortest Path](Graph/kth_shortest_path.cpp)
- [Hierholzer's Algorithm](Graph/Hierholzer.cpp)

## Mathematics

### Number Theory
- [Binary GCD](Math/Number%20theory/binary_gcd.cpp)
- [Chinese Remainder Theorem](Math/Number%20theory/CRT-Online.cpp)
- [Discrete Logarithm](Math/Number%20theory/discrete_log.cpp)
- [Euler Phi](Math/Number%20theory/Euler%20Phi.cpp)
- [Extended Euclidean](Math/Number%20theory/extended_euclidean.cpp)

### Combinatorics
- [NTT Optimized](Math/Counting/ntt_optimized.cpp)
- [Fast Fourier Transform](Math/Counting/FFT.cpp)
- [Matrix Exponentiation](Math/Counting/Matrix_Exponential.cpp)
- [Combinations (nCr)](Math/Counting/nCr.cpp)
- [Lucas Theorem](Math/Counting/lucas.cpp)

### Game Theory
- [Grundy Numbers](Math/Game%20Theory/Grundy%2001.cpp)
- [Matrix Nim](Math/Game%20Theory/Matrix%20Nim.cpp)
- [Misère Nim](Math/Game%20Theory/Misere%20Nim.cpp)
- [Staircase Nim](Math/Game%20Theory/Staircase%20Nim.cpp)

### Geometry
- [3D Geometry](Math/Geometry/3dGeometry.cpp)
- [Circle](Math/Geometry/circle.cpp)
- [Convex Hull](Math/Geometry/convex_hull.cpp)
- [Dynamic Convex Hull](Math/Geometry/dynamic_convex_hull.cpp)
- [Line Operations](Math/Geometry/line.cpp)
- [Polygon](Math/Geometry/polygon.cpp)
- [Sweep Line](Math/Geometry/sweep_line.cpp)

## String Algorithms

### Pattern Matching
- [KMP](String/Basic%20strings%20Algo/KMP.cpp)
- [Z Algorithm](String/Basic%20strings%20Algo/Z_algorithm.cpp)
- [Aho-Corasick](String/Aho%20corasick/AhoCorasick.cpp)
- [Manacher's Algorithm](String/Basic%20strings%20Algo/menacher.cpp)

### Suffix Structures
- [Suffix Array O(nlogn)](String/suffixArray/build_suffixarray_veryfast.cpp)
- [Kasai's LCP](String/suffixArray/Kasai.cpp)
- [Count Pattern](String/suffixArray/problems/count_pattern.cpp)
- [K-th Distinct Substring](String/suffixArray/problems/kth_distinct_substring.cpp)

### Hashing
- [Double Hashing](String/Hashing/double_hashing.cpp)
- [Grid Hashing](String/Hashing/hashing_grid.cpp)
- [K-Hash](String/Hashing/k-hash.cpp)
- [Custom Unordered Map](String/Hashing/custom_unorderd_map.cpp)

## Tree Algorithms

- [Heavy-Light Decomposition](Trees/HLD.cpp)
- [HLD for Edges](Trees/HLD_edges.cpp)
- [Centroid Decomposition](Trees/CentroidDecomposition.cpp)
- [Tree Diameter](Trees/tree_diameter_dfs.cpp)
- [Tree Center](Trees/tree_center.cpp)
- [Tree Center using BFS](Trees/Tree_center_using_bfs.cpp)
- [Tree Isomorphism](Trees/isophrisim.cpp)
- [Tree Flattening](Trees/Tree_flatten.cpp)

## Code Snippets
- [C++17 Build Configuration](Snippet/c++17.sublime-build)
- [Fast I/O Template](Snippet/fastCode.cpp)
- [GCC Optimization](Snippet/gcc_optimize.cpp)
- [Test Case Template](Snippet/TEST_CASE.sublime-snippet)

## Handbook material 

The repository includes:
- [Cheat Sheet](Handbook%20material/Cheat%20Sheet.pdf)
- [Expectation Laws](Handbook%20material/Expectation%20laws.pdf)
- [Serso Library](Handbook%20material/Serso%20Library.pdf)
- [Combination Notes](Notes/combination.md)
- [Hashing Notes](Notes/hashing.md)

---

## Contributing

Feel free to submit pull requests for:
- Bug fixes
- New algorithms
- Optimizations
- Documentation improvements
