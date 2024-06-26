struct Point {
    double x, y, z;
};
long double eps = 1.2e-6;
Point cross(Point a, Point b, Point c) {
    Point result;
    result.x = (b.y - a.y) * (c.z - a.z) - (b.z - a.z) * (c.y - a.y);
    result.y = (b.z - a.z) * (c.x - a.x) - (b.x - a.x) * (c.z - a.z);
    result.z = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return result;
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double TetrahedronVolume(Point a, Point b, Point c, Point d) {
    Point crossProduct = cross(a, b, c);
    Point vectorAD = {d.x - a.x, d.y - a.y, d.z - a.z};
    return dot(crossProduct, vectorAD) / 6.0;
}

bool intersect(Point a, Point b, Point c, Point p, Point q) {
    if (TetrahedronVolume(p, a, b, c) * TetrahedronVolume(q, a, b, c) < 0 &&
        TetrahedronVolume(p, q, a, b) * TetrahedronVolume(p, q, b, c) > 0 &&
        TetrahedronVolume(p, q, b, c) * TetrahedronVolume(p, q, c, a) > 0)
    {
        return true;
    }
    return false;
}
