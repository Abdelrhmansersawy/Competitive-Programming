/*
 * Radix Sort (LSD – Least Significant Digit First)
 *
 * Sorts a list of non-negative integers using radix sort with base 10.
 * It iterates over each digit position, using stable counting sort as a subroutine.
 *
 * Time Complexity: O(d * (n + b))
 *     where:
 *         - n is the size of the array
 *         - d is the number of digits in the maximum number
 *         - b is the base (10 here)
 *
 * Space Complexity: O(n + b)
 *
 * Constraints:
 *     - Only works for non-negative integers.
 *     - The maximum number of digits is limited by the constant `MAX`.
 *
 * Applications in CP:
 *     - Efficient sorting of large arrays of integers when keys are bounded.
 *     - Problems where comparison-based sorts like std::sort (O(n log n)) are too slow.
 *     - Useful for counting inversions in a bounded range.
 *     - Can be adapted to sort tuples or keys using multiple passes.
 */

vector<int> radix_sort(vector<int> v){
    int n = v.size();
    const int MAX = 16; // Max number of digits (adjust if needed)
    ll p10 = 1;
    for(int i = 0; i < MAX; ++i){
        vector<int> f(10), tmp(n);
        for(auto &x : v) f[x / p10 % 10]++;
        for(int i = 1; i < 10; ++i) f[i] += f[i - 1];
        for(int i = n - 1; i >= 0; --i){
            tmp[ --f[v[i] / p10 % 10] ] = v[i];
        }
        swap(v, tmp);
        p10 *= 10;
    }
    return v;
}
