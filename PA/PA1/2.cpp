#include <cstdio>
#include <cstdlib>
typedef long long int64;

const int kN = 4e5 + 5;
int n;
struct Line {
    int x, y;
} p[kN];

/**
 *  @brief Data structure - Fenwick tree.
 *  @details point modification & interval query
*/
struct Fenwick {
    int a[kN];
    void clear() {
        for (int i = 1; i <= n; i++) {
            a[i] = 0;
        }
    }
    void modify(int x) {
        for (; x <= n; x += x & -x) {
            a[x]++;
        }
    }
    int query(int x) {
        int ans = 0;
        for (; x > 0; x ^= x & -x) {
            ans += a[x];
        }
        return ans;
    }
} T;

inline void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}
/**
 *  @brief Calculate number of intersections in the first quadrant
 *  @return Number of intersections.
*/
int64 solve1() {
    T.clear();
    int64 ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += i - 1 - T.query(p[i].x);
        T.modify(p[i].x);
    }
    return ans;
}
/**
 *  @brief Calculate number of intersections in the second and forth quadrant
 *  @return Number of intersections.
*/
int64 solve2() {
    qsort(p + 1, n, sizeof(Line), [](const void *_p, const void *_q) -> int {
        Line *p = (Line*)_p, *q = (Line*)_q;
        return (int64)p->y * q->x < (int64)q->y * p->x ? -1 : 1;
    });
    T.clear();
    int64 ans = 0;
    for (int i = 1, j; i <= n; ) {
        for (j = i; j <= n && (int64)p[i].y * p[j].x == (int64)p[j].y * p[i].x; j++);
        // calculate and modify for all the lines with the same slope at a time
        for (int k = i; k < j; k++) {
            ans += i - 1 - T.query(p[k].y);
        }
        for (int k = i; k < j; k++) {
            T.modify(p[k].y);
        }
        i = j;
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i].x);
        p[i].y = i;
    }
    int64 ans1 = solve1();
    int64 ans2 = solve2();
    // simply swap (x, y) to calculate the forth quadrant
    for (int i = 1; i <= n; i++) {
        swap(p[i].x, p[i].y);
    }
    int64 ans3 = solve2();
    printf("%lld %lld %lld\n", ans1, ans2, ans3);
    return 0;
}