#include <bits/stdc++.h>

const int kN = 1e6 + 5;
int nxt[kN];
char str[kN], pat[kN];

void Kmp(char *str, int n) {
    str[n] = '*';
    nxt[0] = -1;
    int j = 0, t = -1;
    while (j < n) {
        if (t < 0 || str[j] == str[t]) {
            if (str[++j] != str[++t]) {
                nxt[j] = t;
            } else {
                nxt[j] = nxt[t];
            }
        } else {
            t = nxt[t];
        }
    }
}
int Match(char *pat, int n, char *str, int m) {
    int i = 0, j = 0, ans = 0;
    while (i < m) {
        if (j < 0 || str[i] == pat[j]) {
            i++;
            j++;
        } else {
            j = nxt[j];
        }
        if (j == n) {
            ans++;
            j = nxt[j];
        }
    }
    return ans;
}
int main() {
    scanf("%s", str);
    int m = strlen(str);
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%s", pat);
        int n = strlen(pat);
        Kmp(pat, n);
        int ans = Match(pat, n, str, m);
        printf("%d\n", ans);
    }
    return 0;
}