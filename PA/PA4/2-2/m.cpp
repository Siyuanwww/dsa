#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long int64;

const int kN = 1e3 + 5, kM = 1e4 + 5, kBase = 107, kMod = 1e9 + 9;
int n, m, p;
char str[kM][kN];
struct Hash {
    int h, id;
} hash[kM];

int Calc(char *str, int n) {
    int h = 0;
    for (int i = n - 1; i >= 0; i--) {
        h = ((int64)h * kBase + str[i] - 'a') % kMod;
    }
    return h;
}
int Find(int h) {
    int ans = -1;
    for (int l = 0, r = m - 1; l <= r; ) {
        int mid = (l + r) >> 1;
        h <= hash[mid].h ? r = (ans = mid) - 1 : l = mid + 1;
    }
    return ans >= 0 && hash[ans].h == h ? hash[ans].id : -1;
}
int MinRotation(char *str, int n) {
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        if (str[(i + k) % n] == str[(j + k) % n]) {
            k++;
        } else {
            str[(i + k) % n] > str[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
            if (i == j) {
                i++;
            }
            k = 0;
        }
    }
    return i < j ? i : j;
}
int main() {
    scanf("%d%d", &n, &m);
    char tmp[kN];
    for (int i = 0; i < m; i++) {
        scanf("%s", str[i]);
        int k = MinRotation(str[i], n);
        memmove(tmp, str[i], sizeof(char) * k);
        memmove(str[i], str[i] + k, sizeof(char) * (n - k));
        memmove(str[i] + (n - k), tmp, sizeof(char) * k);
        hash[i] = Hash{Calc(str[i], n), i};
    }
    qsort(hash, m, sizeof(Hash), [](const void *x, const void *y) {
        int t = ((Hash*)x)->h < ((Hash*)y)->h ? -1 : 1;
        return ((Hash*)x)->h == ((Hash*)y)->h ? ((Hash*)x)->id - ((Hash*)y)->id : t;
    });
    for (int i = 0; i < m; i++) {
        int x = Find(Calc(str[i], n));
        printf("%d\n", x < 0 || x >= i ? 0 : x + 1);
    }
    return 0;
}