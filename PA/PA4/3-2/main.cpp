#include <cstdio>
#include <cstdlib>
#include <cassert>
typedef long long int64;

#define ls (u << 1)
#define rs (u << 1 | 1)

const int kN = 5e5 + 5;
int n, lim, a[kN], c[kN], mn[kN * 4], f[kN];
int64 b[kN], ans;

inline int min(int x, int y) {
    return x < y ? x : y;
}
void Build(int u, int l, int r, int *a) {
    if (l == r) {
        mn[u] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    Build(ls, l, mid, a);
    Build(rs, mid + 1, r, a);
    mn[u] = min(mn[ls], mn[rs]);
}
int Query(int x, int y, int u, int l, int r) {
    if (x == l && r == y) {
        return mn[u];
    }
    int mid = (l + r) >> 1;
    if (y <= mid) {
        return Query(x, y, ls, l, mid);
    } else if (x > mid) {
        return Query(x, y, rs, mid + 1, r);
    } else {
        return min(Query(x, mid, ls, l, mid), Query(mid + 1, y, rs, mid + 1, r));
    }
}
void Modify(int x, int w) {
    for (; x <= n; x += x & -x) {
        f[x] += w;
    }
}
int Query(int x) {
    int ans = 0;
    for (; x > 0; x ^= x & -x) {
        ans += f[x];
    }
    return ans;
}
int Find(int64 x) {
    int ans = -1;
    for (int l = 1, r = n; l <= r; ) {
        int mid = (l + r) >> 1;
        b[mid] <= x ? l = (ans = mid) + 1 : r = mid - 1;
    }
    return ans;
}
int64 Calc(int l, int r) {
    int64 ans = 0;
    for (int i = r; i >= l; i--) {
        ans += Query(c[i]);
        Modify(c[i], 1);
    }
    for (int i = l; i <= r; i++) {
        Modify(c[i], -1);
    }
    return ans;
}
void Solve(int l, int r) {
    if (r - l + 1 <= lim) {
        if (r - l > 0) {
            ans += Calc(l, r);
        }
        return;
    }
    ans += 2 * (r - l + 1);
    int pos = Query(l, r, 1, 1, n);
    Solve(a[pos] + 1, r);
    Solve(l, a[pos] - 1);
}
int main() {
    scanf("%d%d", &n, &lim);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = ((int64)a[i] + (1LL << 32)) * n + i;
    }
    qsort(b + 1, n, sizeof(int64), [](const void *p, const void *q) {
        int64 t = *((int64*)p) - *((int64*)q);
        return t < 0 ? -1 : t == 0 ? 0 : 1;
    });
    for (int i = 1; i <= n; i++) {
        a[i] = Find(((int64)a[i] + (1LL << 32)) * n + i);
        c[a[i]] = i;
    }
    Build(1, 1, n, c);
    Solve(1, n);
    printf("%lld\n", ans);
    return 0;
}