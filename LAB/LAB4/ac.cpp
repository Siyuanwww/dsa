#include <bits/stdc++.h>

const int kN = 1e6 + 5;
char str[kN], ptn[kN];
int ans[kN];

template <int kN, int kS = 26>
class AhoCorasick {
private:
    int idx, ch[kN][kS], fail[kN], bel[kN];
    int cnt[kN];
    std::vector<int> e[kN];
public:
    AhoCorasick() {
        Clear();
    }
    void Clear() {
        idx = 0;
        NewNode();
    }
    int NewNode() {
        fail[idx] = bel[idx] = -1;
        cnt[idx] = 0;
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
    void GetFail() {
        std::queue<int> q;
        for (int i = 0; i < kS; i++) {
            if (ch[0][i] >= 0) {
                q.push(ch[0][i]);
                fail[ch[0][i]] = 0;
            } else {
                ch[0][i] = 0;
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < kS; i++) {
                if (ch[u][i] >= 0) {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    q.push(ch[u][i]);
                } else {
                    ch[u][i] = ch[fail[u]][i];
                }
            }
        }
    }
    void Query(char *str, int n) {
        int u = 0;
        for (int i = 0; i < n; i++) {
            u = ch[u][str[i] - 'a'];
            cnt[u]++;
            // for (int v = u; v > 0; v = fail[v]) {
            //     if (bel[v] >= 0) {
            //         ans[bel[v]]++;
            //     }
            // }
        }
    }
    void BuildFail() {
        for (int i = 1; i < idx; i++) {
            e[fail[i]].push_back(i);
        }
    }
    void Dfs(int u = 0) {
        for (auto v : e[u]) {
            Dfs(v);
            cnt[u] += cnt[v];
        }
        if (bel[u] >= 0) {
            ans[bel[u]] += cnt[u];
        }
    }
    
};
AhoCorasick<kN, 26> T;

int main() {
    scanf("%s", str);
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%s", ptn);
        int n = strlen(ptn);
        T.Insert(ptn, n, i);
    }
    T.BuildFail();
    int m = strlen(str);
    T.Query(str, m);
    T.BuildFail();
    T.Dfs();
    for (int i = 0; i < t; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}