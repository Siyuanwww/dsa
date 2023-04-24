
#include <algorithm>
struct Point {
    int x, y;
};
class KDTree {
    static const int kN = 5e5 + 5;
    int rt_, top_, id_[kN];
    Point tmp_[kN];
    struct Node {
        Point p;
        int ls, rs;
        int xl, xr, yl, yr;
    } node_[kN];
public:
    int Build(int l, int r) {
        if (l > r) {
            return 0;
        }
        int mid = (l + r) >> 1, u = id_[mid];
        std::nth_element()
    }
    void Flat(int u) {
        if (u == 0) {
            return;
        }
        Flat(node_[u].)
    }
};