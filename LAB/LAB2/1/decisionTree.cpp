#include <bits/stdc++.h>

typedef unsigned int uint;

const int kN = 1600 + 5;
int m, idx, cnt[kN], list[kN];
bool vis[kN], globID3;
FILE *result = fopen("result.out", "w");

struct Data {
    uint info;
    int res;
};
struct Tree {
    std::vector<int> ch[2], crt, res;
    void newNode(int c, int r) {
        ch[0].push_back(-1);
        ch[1].push_back(-1);
        crt.push_back(c);
        res.push_back(r);
    }
    int get(uint info) {
        int u = 0;
        while (res[u] == -1) {
            u = ch[(info >> crt[u]) & 1][u];
        }
        return res[u];
    }
    std::string getAttr(int u) {
        return std::to_string(u) + (crt[u] >= 0 ? ("[" + std::to_string(crt[u]) + "]") : ("(" + std::to_string(res[u]) + ")"));
    }
    void print(int u) {
        if (res[u] == -1) {
            fprintf(result, "%s %s %d\n", getAttr(u).c_str(), getAttr(ch[0][u]).c_str(), 0);
            fprintf(result, "%s %s %d\n", getAttr(u).c_str(), getAttr(ch[1][u]).c_str(), 1);
            print(ch[0][u]);
            print(ch[1][u]);
        }
    }
    
void print_tree(int u, const std::string &prefix = "", bool isLeftChild = false) {
    fprintf(result, "%s", prefix.c_str());
    fprintf(result, "%s", (isLeftChild ? "├──" : "└──"));
    fprintf(result, "%s(%d)\n", (crt[u] >= 0 ? "crt" : "cat"), (crt[u] >= 0 ? crt[u] : res[u]));
    if (ch[0][u] == -1)
        return;

    print_tree(ch[0][u], prefix + (isLeftChild ? "│   " : "    "), true);
    print_tree(ch[1][u], prefix + (isLeftChild ? "│   " : "    "), false);
}
};

// 判断数据集合是否为终止状态
bool isFinal(const std::vector<Data> &vec) {
    bool flg = true;
    int c = vec.front().res;
    for (const auto &data : vec) {
        if (data.res != c) {
            flg = false;
            break;
        }
    }
    if (flg) {
        return true;
    }
    flg = true;
    uint k = vec.front().info;
    for (const auto &data : vec) {
        if (data.info != k) {
            flg = false;
            break;
        }
    }
    return flg;
}
int getRes(const std::vector<Data> &vec) {
    int tot = 0;
    for (auto &data : vec) {
        if (!vis[data.res]) {
            vis[data.res] = true;
            list[tot++] = data.res;
        }
        cnt[data.res]++;
    }
    int p = 0;
    for (int i = 0; i < tot; i++) {
        if (cnt[list[i]] > cnt[list[p]]) {
            p = i;
        }
    }
    for (int i = 0; i < tot; i++) {
        cnt[list[i]] = 0;
        vis[list[i]] = false;
    }
    return list[p];
}
double getEnt(const std::vector<Data> &vec, bool ID3) {
    int tot = 0;
    for (auto &data : vec) {
        if (!vis[data.res]) {
            vis[data.res] = true;
            list[tot++] = data.res;
        }
        cnt[data.res]++;
    }
    int sum = (int)vec.size();
    double ans = 0;
    if (ID3) {
        for (int i = 0; i < tot; i++) {
            ans += 1.0 * cnt[list[i]] / sum * log(1.0 * sum / cnt[list[i]]);
        }
    } else {
        int tmp = 0;
        for (int i = 0; i < tot; i++) {
            tmp += cnt[list[i]] * cnt[list[i]];
        }
        ans = 1.0 - 1.0 * tmp / sum / sum;
    }
    for (int i = 0; i < tot; i++) {
        cnt[list[i]] = 0;
        vis[list[i]] = false;
    }
    return ans;
}
// 在 vec 所包含的数据集上构建决策树，flg 用于标记冗余的属性，最终构建成的树保存在 T 中（使用全局变量 globID3 记录当前的决策树算法）
int dfs(const std::vector<Data> &vec, uint flg, Tree &T) {
    int u = idx++;
    if (isFinal(vec)) {
        T.newNode(-1, getRes(vec));
        return u;
    }
    double min = 1e20;
    int crt = -1;
    for (int i = 0; i < m; i++) {
        if (((flg >> i) & 1) == 0) {
            std::vector<Data> ch[2];
            for (auto &data : vec) {
                ch[(data.info >> i) & 1].push_back(data);
                // 按照属性 i 将数据集分成两个部分
            }
            if (ch[0].size() > 0 && ch[1].size() > 0) {
                double cur = (int)(ch[0].size()) * getEnt(ch[0], globID3) + (int)(ch[1].size()) * getEnt(ch[1], globID3);
                // 对 Gain 和 Gini 进行化简，两种算法都等价于求 |D_v| * Ent/G(D_v) 的最小值
                if (cur < min) {
                    crt = i;
                    min = cur;
                }
            } else {
                flg |= 1 << i;
                // 无效划分
            }
        }
    }
    assert(crt >= 0);
    T.newNode(crt, -1);
    std::vector<Data> ch[2];
    for (auto &data : vec) {
        ch[(data.info >> crt) & 1].push_back(data);
    }
    T.ch[0][u] = dfs(ch[0], flg, T);
    T.ch[1][u] = dfs(ch[1], flg, T);
    // 递归构建子决策树
    return u;
}
Tree build_ID3(const std::vector<Data> &vec) {
    globID3 = true;
    idx = 0;
    Tree T;
    dfs(vec, 0, T);
    return T;
}
Tree build_CART(const std::vector<Data> &vec) {
    globID3 = false;
    idx = 0;
    Tree T;
    dfs(vec, 0, T);
    return T;
}
int main() {
    int n;
    FILE *train = fopen("data_train.in", "r");
    fscanf(train, "%d%d", &n, &m);
    fprintf(result, "train: n = %d, m = %d\n", n, m);
    std::vector<Data> vec(n);
    for (int i = 0; i < n; i++) {
        vec[i].info = 0;
        for (int j = 0; j < m; j++) {
            int x;
            fscanf(train, "%d", &x);
            vec[i].info |= x << j;
        }
        fscanf(train, "%d", &vec[i].res);
    }
    Tree t1 = build_ID3(vec);
    Tree t2 = build_CART(vec);
    fprintf(result, "-------------------------\n");
    t1.print_tree(0);
    fprintf(result, "-------------------------\n");
    t2.print_tree(0);
    fprintf(result, "-------------------------\n");
    FILE *test = fopen("data_test.in", "r");
    FILE *result_ID3 = fopen("result_ID3.out", "w");
    FILE *result_CART = fopen("result_CART.out", "w");
    fscanf(test, "%d%d", &n, &m);
    fprintf(result, "test: n = %d, m = %d\n", n, m);
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++) {
        int res;
        uint info = 0;
        for (int j = 0; j < m; j++) {
            int x;
            fscanf(test, "%d", &x);
            info |= x << j;
        }
        fscanf(test, "%d", &res);
        int ans1 = t1.get(info);
        int ans2 = t2.get(info);
        fprintf(result_ID3, "%d\n", ans1);
        fprintf(result_CART, "%d\n", ans2);
        cnt1 += ans1 == res;
        cnt2 += ans2 == res;
    }
    fprintf(result, "Accuracy\n  ID3: %.5lf\n  CART: %.5lf\n", 1.0 * cnt1 / n, 1.0 * cnt2 / n);
    return 0;
}