int EPS = 10000 , Precision = 4;
long long read(){
    // 1.2345 --> 12345
    string s;cin >> s;
    int x=s.find('.');
    if(x==-1) return stoll(s+"0000");
    string one=s.substr(0,x);
    string two=s.substr(x+1);
    while(two.size()< EPS) two+="0";
    return stoll(one+two);
}
