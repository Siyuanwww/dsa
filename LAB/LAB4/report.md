# LAB4-1 Report

作者：丁思源 2022012901

---

## Task 1

对于字符串 $s_i, i \in [0, n)$，状态 $i$ 表示已经成功匹配了 $i$ 个字符，对于新加入的字符 $c \in \Sigma$，存在转移方程 $trans(i, c)$，可以递归定义 $trans(i, c)$：

$$
trans(i, c) =
\begin{cases}
i + 1 & s_i = c \\
0 & i = 0, s_i \ne c \\
trans(\max(next_i, 0), c) & i > 0, s_i \ne c \\
\end{cases}
$$

可以根据此转移方程构建出所有字符串的 KMP 自动机。

![aaa-Automaton](https://s1.ax1x.com/2023/06/22/pCJkEuD.png)

## Task 2

![ababac-Automaton](https://s1.ax1x.com/2023/06/22/pCJkVDe.png)

## Task 3

由于自动机的状态表示“客观地最多匹配到了多少个字符”，而 KMP 的 next 数组只是一个匹配的辅助工具，因此状态的转移和 next 数组是否改进无关，因此 Task 3 的自动机应该和 Task 2 相同。

![ababac-Automaton](https://s1.ax1x.com/2023/06/22/pCJkVDe.png)

## Task 4

![Trie](https://s1.ax1x.com/2023/06/22/pCJkh26.png)

## Task 5

算法 A：字典树

```cpp
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
```

算法 B：KMP

```cpp
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
```

注意到 Trie 的时间复杂度和“文本串长度 \* 模板串最大长度”有关，而 KMP 的时间复杂度和“模板串总长度 + 模板串数量 \* 文本串长度”有关。可以据此构造测例。

为了使得 Trie 的速度更快，只需要让模板串的数量尽可能多，但是模板串长度可以比较短。具体地，构造一个长度为 $10^6$ 的文本串，$10^3$ 个模板串，模板串长度约为 $10$。

测试结果：算法 A：0.636s，算法 B：2.588s。

为了使得 KMP 的速度更快，只需要让模板串的长度尽可能长，且能够产生较长的前缀匹配，而模板串数量较少。具体地，构造一个长度为 $10^6$ 的文本串 `aaa...a`，$10$ 个模板串，每个模板串长度约为 $10^4$，均包含一个非常长的全“a”前缀。

测试结果：算法 A：25.142s，算法 B：0.083s。

## Task 6

由于竞赛经历，笔者在完成 LAB 之前已经掌握了 AC 自动机，参考资料为 [AC 自动机 - OI Wiki](https://oi-wiki.org/string/ac-automaton/)，使用的工具主要是 Graphviz 用于绘制自动机（包括上面的若干张图片）。

AC 自动机代码：

```cpp
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
```

对拍程序：

`gen.cpp` 用于生成数据:

```cpp
#include <bits/stdc++.h>

std::string generate(int n) {
    std::string str;
    str.resize(n);
    for (int i = 0; i < n; i++) {
        str[i] = rand() % 26 + 'a';
    }
    return str;
}
int main() {
    srand(time(0));
    std::cout << generate(1000000) << '\n';
    int n = 1000;
    std::cout << n << '\n';
    for (int i = 0; i < n; i++) {
        std::cout << generate(4) << '\n';
    }
    return 0;
}
```

`test.sh` 用于批量测试：

```shell
./gen > data/0.in
./ac < data/0.in > data/0a.out
./kmp < data/0.in > data/0k.out
./trie < data/0.in > data/0t.out
diff data/0a.out data/0k.out
diff data/0a.out data/0t.out
```

## Task 7

根据 AC 自动机的算法原理，可以发现其时间复杂度只和节点数量有关（排除输入的必要复杂度）。因此在节点数量较少的情况下，即字符集很小，但是匹配成功率很高、模板串数量很多的情况下。具体地，构造一个长度为 $10^6$ 的几乎全为“a”和“b”的字符串，只包含 $0.1\%$ 的字符“b”，一共 $10^3$ 个全“a”的模板串，每个模板串的长度约为 $10^3$。

测试结果：AC 自动机：0.130s，KMP：2.242s，Trie：3.644s。

在数据随机、模板串数量较少的情况下，三者无法拉开差距。因为此时 KMP 进行的次数较少，Trie 很容易就产生失配的情况。构造一个长度 $10^5$ 的随机字符串，一共 $100$ 个随机模板串，每个模板串的长度为 $10^3$。

测试结果：AC 自动机：0.088s，KMP：0.107s，Trie：0.075s。

## Task 8

字符集很小的时候，可以使用枚举的形式列出 $\Sigma = \{c_1, c_2, \ldots, c_{\lvert \Sigma \rvert}\}$，直接使用一个大小为 $\lvert \Sigma \rvert$ 的数组表示每个节点可能的 $\lvert \Sigma \rvert$ 个子节点。

而字符串很大的时候，每个节点可能的子节点数量无法确定（可能很多也可能非常少），也难以使用枚举的形式完全覆盖整个字符集（如汉字），就算能枚举也会造成极低的空间利用率，此时就需要使用 `std::map` 即平衡树（BBST）记录每个节点的子节点。
