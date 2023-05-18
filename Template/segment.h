class Segment {
    #define ls (u << 1)
    #define rs (u << 1 | 1)
    static const int kN = 1 << 20;
    int n;
    int sum[kN];
    int tag[kN];
    void PushUp(int u) {
        // write your code here
    }
    void Update(int u, int l, int r, int w) {
        // write your code here
    }
    void PushDown(int u, int l, int r) {
        if (tag[u] != 0) {
            int mid = (l + r) >> 1;
            Update(ls, l, mid, tag[u]);
            Update(rs, mid + 1, r, tag[u]);
            tag[u] = 0;
        }
    }
    void Build(int *a, int u, int l, int r) {
        sum[u] = tag[u] = 0;
        if (l == r) {
            sum[u] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        Build(a, ls, l, mid);
        Build(a, rs, mid + 1, r);
    }
    void Modify(int x, int y, int w, int u, int l, int r) {
        if (x == l && r == y) {
            Update(u, l, r, w);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) >> 1;
        if (y <= mid) {
            Modify(x, y, w, ls, l, mid);
        } else if (x > mid) {
            Modify(x, y, w, rs, mid + 1, r);
        } else {
            Modify(x, mid, w, ls, l, mid);
            Modify(mid + 1, w, y, rs, mid + 1, r);
        }
        PushUp(u);
    }
    int Query(int x, int y, int u, int l, int r) {
        if (x == l && r == y) {
            return sum[u];
        }
        PushDown(u, l, r);
        int mid = (l + r) >> 1;
        if (y <= mid) {
            return Query(x, y, ls, l, mid);
        } else if (x > mid) {
            return Query(x, y, rs, mid + 1, r);
        } else {
            return Query(x, mid, ls, l, mid) + Query(mid + 1, y, rs, mid + 1, r);
        }
    }
public:
    void Build(int *a, int _n) {
        Build(a, 1, 1, n = _n);
    }
    void Modify(int l, int r, int w) {
        Modify(l, r, w, 1, 1, n);
    }
    int Query(int l, int r) {
        return Query(l, r, 1, 1, n);
    }
    #undef ls
    #undef rs
} T;