
double cross(const Point<> &a, const Point<> &b){
    return a.x * b.y - b.x * a.y;
}
double triangleAreaBH(double b, double h) {
        return b * h / 2;
}
double triangleArea2sidesAngle(double a, double b, double t) {
        return fabs(a * b * sin(t) / 2);
}

double triangleArea2anglesSide(double t1, double t2,
                double s) {
        return fabs(s * s * sin(t1) * sin(t2) / (2 * sin(t1 + t2)));
}

double triangleArea3sides(double a, double b, double c) {
        double s((a + b + c) / 2);
        return sqrt(s * (s - a) * (s - b) * (s - c));
}

double triangleArea3Points(const Point<> &a, const Point<> &b,
             const Point<> &c) {
        return fabs(cross(a,b) + cross(b,c) + cross(c,a)) / 2;
}

// Cosine Rule
//get angle opposite to side a
double cosRule(double a, double b, double c) {
        // Handle denom = 0
        double res = (b * b + c * c - a * a) / (2 * b * c);
        if (res > 1)
                res = 1;
        if (res < -1)
                res = -1;
        return acos(res);
}

