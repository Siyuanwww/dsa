#include <cstdio>
typedef long long int64;

const int kN = 2e5 + 5;
int n, m, a[kN], b[kN];

/**
 *  @brief Calculate number of intersections in the second and forth quadrant
 *  @param x   x-axis of point
 *  @param y   y-axis of point
 *  @return The area the point belongs to.
*/
int solve(int x, int y) {
    int ans = 0;
    for (int l = 1, r = n; l <= r; ) {
        int mid = (l + r) >> 1;
        // check whether the point (x, y) is at the upper(inclusive) part of line
        if ((int64)x * b[mid] + (int64)y * a[mid] >= (int64)a[mid] * b[mid]) {
            l = (ans = mid) + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", solve(x, y));
    }
    return 0;
}