#include <bits/stdc++.h>

const int kN = 1e6 + 5;
int ans[kN];
char str[kN], ptn[kN];

template <int kN, int kS = 26>
class Trie {
private:
    int idx, bel[kN], ch[kN][kS];
public:
    Trie() {
        Clear();
    }
    void Clear() {
        idx = 0;
        NewNode();
    }
    int NewNode() {
        bel[idx] = -1;
        std::fill(ch[idx], ch[idx] + kS, -1);
        return idx++;
    }
    void Insert(char *str, int n, int id) {
        int u = 0;
        for (int i = 0; i < n; i++) {
            int c = str[i] - 'a';
            if (ch[u][c] < 0) {
                ch[u][c] = NewNode();
            }
            u = ch[u][c];
        }
        bel[u] = id;
    }
    void Query(char *str, int n) {
        int u = 0;
        for (int i = 0; i < n; i++) {
            int c = str[i] - 'a';
            if (ch[u][c] >= 0) {
                u = ch[u][c];
            } else {
                break;
            }
            if (bel[u] >= 0) {
                ans[bel[u]]++;
            }
        }
    }
};
Trie<kN, 26> T;

int main() {
    scanf("%s", str);
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%s", ptn);
        int n = strlen(ptn);
        T.Insert(ptn, n, i);
    }
    int m = strlen(str);
    for (int i = 0; i < m; i++) {
        T.Query(str + i, m - i);
    }
    for (int i = 0; i < t; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}