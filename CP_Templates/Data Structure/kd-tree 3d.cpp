struct Point {
    long double x, y, z;
    Point(long double x , long double y , long double z):x(x) , y(y) , z(z){}
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && (y < p.y || (y == p.y && z < p.z)));
    }
};
 
class KDTree {
private:
    struct Node {
        Point point;
        Node* left;
        Node* right;
        Node(Point p) : point(p), left(nullptr), right(nullptr) {}
    };
    Node* root;
 
    Node* build(vector<Point>& points, int depth) {
        if (points.empty()) return nullptr;
        int axis = depth % 3;
        sort(points.begin(), points.end(), [axis](Point a, Point b) {
            if (axis == 0) return a.x < b.x;
            if (axis == 1) return a.y < b.y;
            return a.z < b.z;
        });
        int mid = points.size() / 2;
        Node* node = new Node(points[mid]);
        vector<Point> leftPoints(points.begin(), points.begin() + mid);
        vector<Point> rightPoints(points.begin() + mid + 1, points.end());
        node->left = build(leftPoints, depth + 1);
        node->right = build(rightPoints, depth + 1);
        return node;
    }
 
    long double dist(Point p1, Point p2) {
        long double res = (p1.x - p2.x) * (p1.x - p2.x);
        res += (p1.y - p2.y) * (p1.y - p2.y);
        res += (p1.z - p2.z) * (p1.z - p2.z);
        return sqrtl(res);
    }
 
    void nearest(Node* node, Point target, int depth, long double& bestDist) {
        if (!node) return;
        long double currentDist = dist(node->point, target);
        if (currentDist < bestDist && currentDist > 0) bestDist = currentDist;  // Added currentDist > 0 check
 
        int axis = depth % 3;
        Node* next = (axis == 0 ? target.x < node->point.x :
                    (axis == 1 ? target.y < node->point.y : target.z < node->point.z)) ? node->left : node->right;
        Node* other = next == node->left ? node->right : node->left;
 
        nearest(next, target, depth + 1, bestDist);
 
        long double axisDist = (axis == 0 ? abs(target.x - node->point.x) :
                              (axis == 1 ? abs(target.y - node->point.y) : abs(target.z - node->point.z)));
        if (axisDist < bestDist) {
            nearest(other, target, depth + 1, bestDist);
        }
    }
 
    void findMinDistanceHelper(Node* node, long double& minDist) {
        if (!node) return;
 
        // Find nearest point to current node's point
        long double currentMin = numeric_limits<long double>::max();
        nearest(root, node->point, 0, currentMin);
        minDist = min(minDist, currentMin);
 
        // Recurse on children
        findMinDistanceHelper(node->left, minDist);
        findMinDistanceHelper(node->right, minDist);
    }
 
public:
    KDTree(vector<Point>& points) {
        root = build(points, 0);
    }
 
    long double nearest(Point target) {
        long double bestDist = numeric_limits<long double>::max();
        nearest(root, target, 0, bestDist);
        return bestDist;
    }
 
    long double findMinDistance() {
        if (!root || (!root->left && !root->right)) return numeric_limits<long double>::max();
        long double minDist = numeric_limits<long double>::max();
        findMinDistanceHelper(root, minDist);
        return minDist;
    }
};
