/*
    #Stirling numbe
    1. S(r, n), represents the number of ways that we can arrange r objects around indistinguishable circles of length n,
    and every circle n must have at least one object around it.
    2. S(n,k) as the different ways to cut n different elements into k undifferentiated non-empty subsets. For example, S(5,3) denotes to:25
     
    S[i][j] = S[i-1][j-1] + s[i-1][j] *( i-1)
    Time Complexity : O(r * n)
    Auxiliary Space : O(r * n)
*/
int stirling_number(int n,int k){
    if(k==0)return n==0;
    if(n==0)return 0;
    return stirling_number(n-1,k-1)+(n-1)* stirling_number(n-1,k);

}