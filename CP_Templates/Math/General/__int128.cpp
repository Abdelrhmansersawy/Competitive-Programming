__int128 read(){
    __int128 ans = 0;
    int sgn = 1;
    char c = getchar();
    while (!isdigit(c)){
        if (c == '-')
            sgn *= -1;
        c = getchar();
    }
    while (isdigit(c)){
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans * sgn;
}
void print(__int128 x){
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
