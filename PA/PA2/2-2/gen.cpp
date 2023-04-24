#include <bits/stdc++.h>

int main() {
    srand(time(0));
    int n = 4, m = 4, nn = 3, mm = 3;
    printf("%d %d %d %d\n", n, m, nn, mm);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x = rand() % 10;
            printf("%d%c", x < 5 ? 1 : 0, " \n"[j == m]);
        }
    }
    return 0;
}