#include <cstdio>
#include <algorithm>
const int kN = 2e3 + 5, kMod = 10007;
int n, m, nn, mm, sum[kN][kN];
int main() {
    scanf("%d%d%d%d", &n, &m, &nn, &mm);
    std::swap(n, m);
    std::swap(nn, mm);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (x == 1);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int p = i; p > 0 && i - p + 1 <= nn; p--) {
                for (int q = j; q > 0 && j - q + 1 <= mm; q--) {
                    ans += (sum[i][j] + sum[p - 1][q - 1] - sum[i][q - 1] - sum[p - 1][j]) == (i - p + 1) * (j - q + 1);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}