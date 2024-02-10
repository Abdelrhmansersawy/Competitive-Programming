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

double triangleArea3points(const point &a, const point &b,
			 const point &c) {
        return fabs(cross(a,b) + cross(b,c) + cross(c,a)) / 2;
}
