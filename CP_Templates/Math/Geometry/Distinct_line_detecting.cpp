//ay + bx = c
void fix(int &a, int &b, int &c){
    int g = __gcd(__gcd(a,b),c);
    a/=g,b/=g,c/=g;
    if(a < 0 || (a == 0 && b < 0))
    {
        a*=-1, b*=-1, c*=-1;
    }
}
array<int,3> Line(int dx, int dy, Point P)
{
    int a = dx;
    int b = -dy;
    int c = P.y() * a + P.x() * b;
    fix(a,b,c);
    return {a,b,c};
}
