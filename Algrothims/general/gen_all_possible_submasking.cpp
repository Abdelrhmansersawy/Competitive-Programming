/*
	----> Generating All possible submasks <-----
	- Iterating through all masks with their submasks. Complexity  O(3^n)
*/
// m : mask , s : submask
for (int m=0; m<(1<<n); ++m)
    for (int s=m; s; s=(s-1)&m)
