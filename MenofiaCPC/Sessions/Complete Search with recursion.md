# Complete Search with recursion
## Objectives:
- ~~Dealing with recursion~~
- Generate all subsets.
	- ~~Recursively~~
	- with Bitmasks.
- Permutations
	- Generating all Permutations
		-  Recursively
		- Using ``next_permutation()`` builtin function in C++.
	- Lexicographical Order
		- Fnding minimum lexicographical order.
		- Finding maximum lexicographical order.
- Backtracking
	- Standard Problems
		- 8 Queens $O(n! * 2^{n})$.
		- Generate all possible paths in the grid $O(2^{n+m})$.
		- Flood Fill (From $O(2^{n+m})$ to $O(n * m)$ ).
	- Tips  (!very Important)
		- Filtering versus Generating.
			- Try to solve **8 Queen** problem in $O(n! *n)$
		- Prune Infeasible Search Space Early.
		- Utilize Symmetries.
***

# Material:
| Videos | Blogs | Books |
| ---- | ---- | ---- |
| [Backtracking, 8 Queen (Dr. Mostafa Saad)](https://www.youtube.com/watch?v=hLXVhRzqq18&list=PLPt2dINI2MIYmHYBSEdkdKMf_3nzFMveo&index=12) | [How Recursion Works](https://www.freecodecamp.org/news/how-recursion-works-explained-with-flowcharts-and-a-video-de61f40cb7f9/) | [Complete Search](https://usaco.guide/CP2.pdf#page=55) |
| [Backtracking (Eng. Ahmed Ali)](https://www.youtube.com/watch?v=bj2Qdu08XYw) | [Subset](https://usaco.guide/bronze/complete-rec#subsets) | [Generating subsets](https://usaco.guide/CPH.pdf#page=57) |
| [recursion & Backtracking (Mr algortthims)](https://www.youtube.com/playlist?list=PLR5x_RGTMNNXHdQp1EorhZq-t3TOWCNis) | [Permutations](https://usaco.guide/bronze/complete-rec#permutations) | [Generating permutations](https://usaco.guide/CPH.pdf#page=59) |
| [Backtracking (Abdul Bari)](https://www.youtube.com/watch?v=DKCbsiDBN6c) | [Backtracking](https://usaco.guide/bronze/complete-rec#backtracking) | [Backtracking](https://usaco.guide/CPH.pdf#page=60) |
| --  | [(!options) how next_permtation() works](https://marknelson.us/posts/2002/03/01/next-permutation.html) | -- |

[Sheet Link](https://vjudge.net/contest/606331#overview)
