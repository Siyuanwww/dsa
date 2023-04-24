#include <bits/stdc++.h>

int main() {
    int n = 500000, m = 500000;
    for (int i = 0; i < n; i++) {
        printf("%c", 'A' + i % 26);
    }
    printf("\n");
    printf("%d\n", m);
    for (int i = 0; i < m; i++) {
        printf("%d %c\n", 0, 'A' + i % 26);
    }
    return 0;
}