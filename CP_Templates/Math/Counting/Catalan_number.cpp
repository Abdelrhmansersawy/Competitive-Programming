/*
 * Catalan Numbers C_n
 * -------------------
 * Formula:
 *   C_n = (1 / (n+1)) * (2n choose n)
 *       = (2n)! / ((n+1)! * n!)
 *
 * Interpretations:
 *
 * 1) Correct Bracket Sequences
 *    - Take n '(' and n ')'.
 *    - Count sequences that are valid: 
 *      every prefix has #open ≥ #close.
 *    - Eg (n=3): "((()))", "(()())", "()()()", ...
 *
 * 2) Rooted Full Binary Trees
 *    - Binary tree where every node has 0 or 2 children.
 *    - With (n+1) leaves, number of different tree shapes = C_n.
 *    - Example n=2: 2 possible full binary trees with 3 leaves.
 *
 * 3) Parenthesizations of (n+1) Factors
 *    - Product: x1 * x2 * ... * x(n+1).
 *    - Count ways to put parentheses so order of multiplication
 *      is fully specified.
 *    - Eg (n=2 → 3 factors): (x1*(x2*x3)), ((x1*x2)*x3).
 *
 * 4) Polygon Triangulations
 *    - Convex polygon with (n+2) sides.
 *    - Count how many ways to draw non-crossing diagonals 
 *      so polygon is divided into triangles.
 *
 * 5) Non-crossing Chords in Circle
 *    - Place 2n points on a circle.
 *    - Count ways to connect them with n chords such that
 *      no two chords intersect inside circle.
 *
 * 6) Full Binary Trees (Non-isomorphic)
 *    - Count different *shapes* of full binary trees with n internal nodes.
 *    - “Non-isomorphic” = we don’t care about node labels, only structure.
 *
 * 7) Monotonic Lattice Paths
 *    - Grid n×n.
 *    - Count paths from (0,0) → (n,n) using only right (R) and up (U) moves.
 *    - Restriction: path never goes above line y=x.
 *
 * 8) Stack-sortable Permutations
 *    - Permutations of length n that can be sorted using a single stack.
 *    - Stack operation: push input numbers in order, pop anytime to output.
 *    - Equivalently: permutations with no "231 pattern".
 *      (no i<j<k with a_k < a_i < a_j).
 *
 * 9) Non-crossing Partitions
 *    - Partition set {1..n} into groups (blocks).
 *    - Place elements {1..n} around a circle.
 *    - Connect all elements of the same block with chords.
 *    - Condition: chords cannot cross inside the circle.
 *
 *    Important: a block may have size > 2
 *      • Example (n=4):
 *         {1,2,3,4} → all in one block → valid 
 *         {1,2,3}, {4} → valid 
 *         {1,3}, {2,4} → invalid  (chords cross)
 *
 *    So blocks can be singletons, pairs, triples, etc.,
 *    as long as no two connections cross.
 *
 * 10) Ladder Coverings
 *    - Ladder = columns of heights 1..n.
 *    - Count ways to cover it with exactly n rectangles.
 *    - Each rectangle must fully cover some contiguous columns.
 *
 * Catalan numbers show up in:
 *   - Combinatorics
 *   - Geometry
 *   - Tree structures
 *   - Dynamic programming
 */
