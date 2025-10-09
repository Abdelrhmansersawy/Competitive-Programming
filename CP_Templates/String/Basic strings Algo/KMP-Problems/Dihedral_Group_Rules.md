### Dihedral Group Rules (for string length = |t|)

These are the basic laws for how rotations (`R`) and inversions (`I`) combine:

1. `R(x) R(y) = R(x + y)`
   → two rotations just add up.

2. `I R(x) = R(-x) I`
   → moving an inversion past a rotation flips the direction.
   (same as `I R(x) = R(|t| - x) I`)

3. `I I = R(0)`
   → two inversions cancel out (no change).

4. `R(x) I = I R(|t| - x)`
   → moving a rotation past an inversion reverses its direction.

5. `L(x) = R(|t| - x)`
   → a left rotation by x is equivalent to a right rotation by (|t| - x).

---

### Inverses

* The inverse of a rotation `R(t, a)` is `R(t, |t| − a)`
* Any `I R(a)` is its **own inverse** (doing it twice cancels out).

That means:
If you apply I R(a) twice, you get the original string back.
