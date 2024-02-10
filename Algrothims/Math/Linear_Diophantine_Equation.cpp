/*
   ## Linear Diophantine Equation
   A Linear Diophantine Equation (in two variables) is an equation of the general form:
    a.x + b.y = c
  where a,b are given intergs, and x,y are unknown integers.
  
  In this code, we consider several classical problems on these equations:
  
  1. finding one solution
  2. finding all solutions
  3. finding the number of solutions and the solutions themselves in a given interval
  4.finding a solution with minimum value of  x + y$
*/

// ## Finding one solution
int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

// ## Find number of solution when x: [minx, maxx] , y: [miny,maxy]
void shift_solution(int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    int rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
}
/*
  ## finding the number of solutions and the solutions themselves in a given interval
  Once we have lx and rx.
  Just need to iterate through
  x = lx + k * (b / g) for all k >= 0 until x = rx
  and find the corresponding y values using the equation a.x + b.y = c
*/

/*
  ## Find the solution with minimum value of x + y
  Here x  and y also need to be given some restriction, otherwise, the answer may become negative infinity.
  1. Find any solution (x , y) for the equations.
  
  minimum value = x + y + k * (b - a) / g
  
  if(a < b) select smallest possible value of  k
  if(a > b) select the largest possible value of k
  if(a == b) all solution will have the same sum x + y. 

*/
