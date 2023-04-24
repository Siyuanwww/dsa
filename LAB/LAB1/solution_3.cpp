#include <cstdio>
#include <ctime>
#include <iostream>
typedef long long int64;

const int kN = 2e3 + 5;
int n, m, q, a[kN][kN];
int64 sum[kN][kN];

/**
 *  @brief Calculate 2-dimensional sum  
*/
inline int64 query(int a, int b, int c, int d) {
    return sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1];
}
int main() {
    auto s = clock();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + a[i][j];
        }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int x, y, a, b;
        scanf("%d%d%d%d", &x, &y, &a, &b);
        printf("%lld\n", query(x, y, x + a - 1, y + b - 1));
    }
    std::cerr << clock() - s << std::endl;
    return 0;
}