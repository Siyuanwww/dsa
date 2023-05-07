#include <cstdio>
#include <cstring>

const int kN = 1e3 + 5, kM = 1e4 + 5;
int n, m, p, nxt[2 * kN * kM];
char str[kM][kN], pat[2 * kN * kM];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", str[i] + 1);
        memcpy(pat + p + 1, str[i] + 1, m * sizeof(char));
        p += m;
        memcpy(pat + p + 1, str[i] + 1, m * sizeof(char));
        p += m;
        pat[p] = '#';
    }
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= p; i++) {
        for (; j > 0 && pat[j + 1] != pat[i]; j = nxt[j]);
        if (pat[j + 1] == pat[i]) {
            j++;
        }
        nxt[i] = j;
    }
    for (int i = 1; i <= n; i++) {
        // printf("%d\n", solve(str[i]));
    }
    return 0;
}