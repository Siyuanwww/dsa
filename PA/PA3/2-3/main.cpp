#include <cstdio>
#include <cstdlib>
#include <cassert>
typedef long long int64;

const int kN = 4e5 + 5;
int n, m, b[kN];

struct Info {
    char opt;
    int l, r;
} q[kN];

// 经典的线段树
class Segment {
    #define ls (u << 1)
    #define rs (u << 1 | 1)
    static const int kN = 1 << 20;
    int64 sum[kN];
    int tag[kN];
    void PushUp(int u) {
        sum[u] = sum[ls] + sum[rs];
    }
    void Update(int u, int l, int r, int w) {
        tag[u] += w;
        sum[u] += (int64)w * (b[r] - b[l - 1]);
        // 需要注意 l ~ r 对应的实际长度需要在数组 b 中查找，即 (b_{l - 1}, b_{r}]
    }
    void PushDown(int u, int l, int r) {
        if (tag[u] != 0) {
            int mid = (l + r) >> 1;
            Update(ls, l, mid, tag[u]);
            Update(rs, mid + 1, r, tag[u]);
            tag[u] = 0;
        }
    }
public:
    void Modify(int x, int y, int u, int l, int r) {
        if (x == l && r == y) {
            Update(u, l, r, 1);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) >> 1;
        if (y <= mid) {
            Modify(x, y, ls, l, mid);
        } else if (x > mid) {
            Modify(x, y, rs, mid + 1, r);
        } else {
            Modify(x, mid, ls, l, mid);
            Modify(mid + 1, y, rs, mid + 1, r);
        }
        PushUp(u);
    }
    int64 Query(int x, int y, int u, int l, int r) {
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
    #undef ls
    #undef rs
} T;

// 查找 x 在离散化后的值，也就是对应的 b 数组中的下标
int find(int x) {
    int ans = 0;
    for (int l = 1, r = n; l <= r; ) {
        int mid = (l + r) >> 1;
        b[mid] <= x ? l = (ans = mid) + 1 : r = mid - 1;
    }
    assert(ans >= 0);
    return ans;
}
int main() {
    scanf("%d%d", &n, &m);
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        char str[5];
        scanf("%s%d%d", str, &q[i].l, &q[i].r);
        q[i].opt = str[0];
        b[++tot] = q[i].l - 1;
        // 可以理解成点 r 管辖了从它（包括）到上一个点（不包括）之间所有的点，因此应该对 l - 1 进行离散化
        b[++tot] = q[i].r;
    }
    std::qsort(b + 1, tot, sizeof(int), [](const void *x, const void *y) {
        return *(int*)x - *(int*)y;
    });
    n = 0;
    for (int i = 1; i <= tot; i++) {
        if (b[i] != b[i - 1]) { // 经典的离散化操作
            b[++n] = b[i];
        }
    }
    for (int i = 1; i <= m; i++) {
        if (q[i].opt == 'H') {
            T.Modify(find(q[i].l - 1) + 1, find(q[i].r), 1, 1, n);
            // l - 1 这个点管辖了它之前的一段，因此找到 l - 1 对应的离散化后的点之后，需要 +1 才可以
        } else {
            printf("%lld\n", T.Query(find(q[i].l - 1) + 1, find(q[i].r), 1, 1, n));
        }
    }
    return 0;
}