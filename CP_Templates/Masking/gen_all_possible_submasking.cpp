/*
 * ======================= Submask Generation Note =======================
 *
 * Description:
 * - Iterating over all submasks of all masks (excluding 0-submask).
 * - Common in bitmask DP and inclusion-exclusion problems.
 * - Time Complexity: O(3^n) total over all masks.
 * 
 * Pattern 1: Iterate over all submasks of a mask `m`.
 * Variables:
 *   - m : the current mask
 *   - s : the current submask of m (s ≠ 0)
 *
 * Pattern 2: Iterate over all supermasks that contain mask `m` as a subset.
 * Variables:
 *   - m : the base mask
 *   - s : current supermask (s ⊇ m)
 * 
 * ======================================================================
 */

// Pattern 1
for (int m = 0; m < (1 << n); ++m)
    for (int s = m; s; s = (s - 1) & m);

// Pattern 2
for (int m = 0; m < (1 << n); ++m)
    for (int s = m; s < (1 << n); s = (s + 1) | m);
