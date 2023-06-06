#include <algorithm>

typedef int Point[2];
struct Compare {
    int opt;
    bool operator()(const Point *p, const Point *q) {
        return p[opt] < q[opt];
    }
} cmp;
class KDTree {
    static const int kN = 5e5 + 5;
    int rt, top, id[kN];
    Point tmp[kN];
    struct Node {
        Point p;
        int ls, rs;
        int min[2], max[2];
    } node[kN];
    void PushUp(int u) {
        for (int i = 0; i <= 1; i++) {
            node[u].min[i] = node[u].max[i] = node[u].p[i];
            if (node[u].ls) {
                node[u].xl = std::min(node[u].xl, node[node[u].ls].xl);
                node[u].xr = std::max(node[u].xr, node[node[u].ls].xr);
            }
        }
    }

public:
    int Build(int l, int r, int d) {
        if (l > r) {
            return 0;
        }
        int mid = (l + r) >> 1, u = id[mid];
        cmp.opt = d;
        std::nth_element(tmp + l, tmp + mid, tmp + r + 1, cmp);
        node[u].p = tmp[mid];
        node[u].ls = Build(l, mid - 1, d ^ 1);
        node[u].rs = Build(mid + 1, r, d ^ 1);
        PushUp(u);
        return u;
        // std::nth_element() todo
    }
    void Flat(int u) {
        if (u == 0) {
            return;
        }
        id[++top] = u;
        tmp[top] = node[u].p;
        Flat(node[u].ls);
        Flat(node[u].rs);
    }
};