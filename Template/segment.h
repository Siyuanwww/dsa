class Segment {
    #define ls (u << 1)
    #define rs (u << 1 | 1)
    static const int kN = 1 << 20;
    int n_;
    int sum_[kN];
    int tag_[kN];
    void PushUp(int u) {
        // write your code here
    }
    void Update(int u, int l, int r, int w) {
        // write your code here
    }
    void PushDown(int u, int l, int r) {
        if (tag_[u] != 0) {
            int mid = (l + r) >> 1;
            Update(ls, l, mid, tag_[u]);
            Update(rs, mid + 1, r, tag_[u]);
            tag_[u] = 0;
        }
    }
    void Build(int u, int l, int r) {
        sum_[u] = tag_[u] = 0;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        Build(ls, l, mid);
        Build(rs, mid + 1, r);
    }
    void Modify(int x, int y, int u, int l, int r, int w) {
        if (x == l && r == y) {
            Update(u, l, r, w);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) >> 1;
        if (y <= mid) {
            Modify(x, y, ls, l, mid, w);
        } else if (x > mid) {
            Modify(x, y, rs, mid + 1, r, w);
        } else {
            Modify(x, mid, ls, l, mid, w);
            Modify(mid + 1, y, rs, mid + 1, r, w);
        }
        PushUp(u);
    }
    int Query(int x, int y, int u, int l, int r) {
        if (x == l && r == y) {
            return sum_[u];
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
    void set_size(int n) {
        Build(1, 1, n_ = n);
    }
    void Modify(int l, int r, int w) {
        Modify(1, 1, n_, l, r, w);
    }
    int Query(int l, int r) {
        return Query(l, r);
    }
    #undef ls
    #undef rs
} T;