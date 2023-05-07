#include <cstdio>
#include <cstdlib>
#include <cassert>
typedef long long int64;

#define ls (u << 1)
#define rs (u << 1 | 1)

const int kN = 5e5 + 5;
int n, lim, a[kN], c[kN], mn[kN * 4], f[kN];
// a 是离散化后的数组，其中规定了值相同时靠后者更大，因此 a 是一个 1~n 的排列
// c 记录了值为 i 的元素在 a 中的下标
int64 b[kN], ans;

inline int min(int x, int y) {
    return x < y ? x : y;
}
// 使用线段树求区间最小值
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
// 使用树状数组求逆序对
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
// 求逆序对
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
    if (r - l + 1 <= lim) { // 当值域大小（等价于元素个数）在 lim 范围内时，直接求逆序对
    /**
     * 不过值得注意的是，应该求的逆序对是：从 a 中找出值为 l~r 的元素，并在 a 中求逆序对
     * 但是发现 a(i) = v, c(v) = i; a(j) = w, c(w) = j
     * 如果两个元素 a(i), a(j) 构成逆序对，当且仅当 c(v) 和 c(w) 构成逆序对
     * 因此可以直接在 c 中求 l~r 这个子序列的逆序对
     */
        if (r - l > 0) {
            ans += Calc(l, r);
        }
        return;
    }
    ans += 2 * (r - l + 1);
    int pos = Query(l, r, 1, 1, n); // 找到值在 l~r 范围内的最小下标，即 quicksort 中对应的 L
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