/*
	#Z-algorithm
	
	The Z function is an algorithm that takes a string as an input, and return a list of integers of size same as that of the string, such that Z[i] will represent the length of the longest matching prefix of the original string, which matches with the string if it had started at the ith position, and all of it is done in linear time.
	
	Time Complexity: O(n + m) // n = length of 1st string, m = length of 2nd string.
	Space Complexity: O(n + m)

*/
vector<int> zFunction(string s, int n) {
    vector<int> z(n);
    int left = 0, right = 0;
    for(int i = 1; i < n; i++) {
        if(i <= right) {
            z[i] = min(right - i + 1, z[i - left]);
        }
        while(i + z[i] < n && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if(i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}
int findStartIndexOfSubstring(string s1, string s2) {
	string mixed = s2 + "$" + s1;
    vector<int> getZ = zFunction(mixed, mixed.length());
	for(int i = 0; i < mixed.length(); i++) {
		if(getZ[i] == s2.length()) {
			return (i - s2.length() - 1);
		}
	}
	return -1;
}
