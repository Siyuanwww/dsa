#include <cstdio>
#include <cstdlib>
typedef long long int64;
typedef unsigned long long uint64;

const int kN = 1e3 + 5, kM = 1e4 + 5, kBase = 107, kMod = 1e9 + 9;
int n, m, p;
uint64 pw[kN], suf[kN];
char str[kM][kN];
struct Hash {
    uint64 h;
    int id;
} hash[kM];

uint64 Calc(char *str, int n) {
    uint64 h = 0;
    for (int i = n - 1; i >= 0; i--) {
        h = h * kBase + str[i] - 'a';
    }
    return h;
}
// 判断哈希值是否存在
int Find(Hash *hash, uint64 h) {
    int ans = -1;
    for (int l = 0, r = m - 1; l <= r; ) {
        int mid = (l + r) >> 1;
        h <= hash[mid].h ? r = (ans = mid) - 1 : l = mid + 1;
    }
    return ans >= 0 && hash[ans].h == h ? hash[ans].id : -1;
}
int Appear(char *str, int n) {
    for (int i = n - 1; i >= 0; i--) { // 记录后缀的哈希值，用于计算循环位移之后的哈希值
        suf[i] = suf[i + 1] * kBase + str[i] - 'a';
    }
    uint64 h = 0;
    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        h += pw[i] * (str[i] - 'a');
        uint64 t = suf[i + 1] + h * pw[n - 1 - i]; // 两部分组合后的哈希值
        int x = Find(hash, t);
        if (x >= 0) { // 判断哈希值是否存在
            ans = x < ans ? x : ans;
        }
    }
    return ans > 1e8 ? -1 : ans;
}
int main() {
    scanf("%d%d", &n, &m);
    pw[0] = 1;
    for (int i = 1; i < n; i++) {
        pw[i] = pw[i - 1] * kBase;
    }
    for (int i = 0; i < m; i++) {
        scanf("%s", str[i]);
        hash[i] = Hash{Calc(str[i], n), i};
    }
    qsort(hash, m, sizeof(Hash), [](const void *x, const void *y) {
        int t = ((Hash*)x)->h < ((Hash*)y)->h ? -1 : 1;
        return ((Hash*)x)->h == ((Hash*)y)->h ? ((Hash*)x)->id - ((Hash*)y)->id : t;
    });
    for (int i = 0; i < m; i++) {
        int x = Appear(str[i], n);
        printf("%d\n", x < 0 || x >= i ? 0 : x + 1);
    }
    return 0;
}