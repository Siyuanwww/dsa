#include <algorithm>

struct Point {
    int x, y;
};
class KDTree {
    static const int kN = 5e5 + 5;
    int rt, top, id[kN];
    Point tmp[kN];
    struct Node {
        Point p;
        int ls, rs;
        int xl, xr, yl, yr;
    } node[kN];
public:
    int Build(int l, int r) {
        if (l > r) {
            return 0;
        }
        int mid = (l + r) >> 1, u = id[mid];
        // std::nth_element() todo
    }
    void Flat(int u) {
        if (u == 0) {
            return;
        }
        Flat(node[u].ls);
        id[++top] = u;
        Flat(node[u].rs);
    }
};