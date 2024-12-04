// Define int128 types and I/O operators
typedef __int128 int128;
typedef unsigned __int128 uint128;
 
// Helper functions for int128 I/O
ostream& operator << (ostream &os, int128 num) {
    string str;
    if(num == 0) return os << "0";
    bool neg = false;
    if(num < 0) {
        neg = true;
        num = -num;
    }
    while(num) {
        str.push_back('0' + num % 10);
        num /= 10;
    }
    if(neg) str.push_back('-');
    reverse(str.begin(), str.end());
    return os << str;
}
 
istream& operator >> (istream &is, int128 &num) {
    string str;
    is >> str;
    num = 0;
    bool neg = false;
    for(char c : str) {
        if(c == '-') neg = true;
        else num = num * 10 + (c - '0');
    }
    if(neg) num = -num;
    return is;
}
