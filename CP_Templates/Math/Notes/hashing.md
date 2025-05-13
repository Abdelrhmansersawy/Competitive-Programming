## Permutation hashing
Let $P={a,b,c}$

$H(P) = (a \times x^3 + b \times x^2 + c \times x)$ , such that 
- $x$ is a random number $\ge 27$

## Set hashing
Let $S$ = ${a , b , c}$

$H(S) = (a + k)^h + (b + k)^h + (c + k)^h$, such that 
- h small random number
- k larger random number
## Xor hashing
Let $S$ = ${a , b , c}$

$H(S) = (a + k) \oplus (b + k) \oplus (c + k)$, such that
- K  larger random number
*Take care of repetition in s, because $(a + k) \oplus (a + k) = 0$*

