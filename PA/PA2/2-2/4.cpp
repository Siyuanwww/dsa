#include <cstdio>

const int kN = 2e3 + 5, kMod = 10007;
int n, m, nn, mm, sum[kN][kN];
struct Info {
    int val, id, ans;
};
// 实现了一个双端队列
struct Deque {
    Info a[kN];
    int head, tail;
    Deque() : head(0), tail(0) {}
    void clear() {
        head = tail = 0;
    }
    bool empty() {
        return head == tail;
    }
    Info &back() {
        return a[tail - 1];
    }
    Info &front() {
        return a[head];
    }
    void push(int val, int id, int ans) {
        a[tail++] = Info{val, id, ans};
    }
    void pop_back() {
        tail--;
    }
    void pop_front() {
        head++;
    }
} q;

inline void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}
inline int max(const int &x, const int &y) {
    return x > y ? x : y;
}
inline int min(const int &x, const int &y) {
    return x < y ? x : y;
}
inline void add(int &x, int y) {
    (x += y) >= kMod && (x -= kMod);
}
inline void sub(int &x, int y) {
    (x -= y) < 0 && (x += kMod);
}
int solve(int *sum) {
    for (int i = 1; i <= m; i++) {
        sum[i] = min(sum[i], nn);
    }
    q.clear();
    int ans = 0, cur = 0;
    for (int i = 1; i <= m; i++) {
        /*
          实现了一个从队首到队尾单调不减的单调队列
          队列中每个元素是一个 triple，分别是位置 id，向上的高度 val，以 id 为右下角的矩形有 ans 个
        */
        for (; !q.empty() && q.back().val > sum[i]; ) {
            sub(cur, q.back().ans);
            q.pop_back();
        }
        if (!q.empty()) {
            if (q.front().id == i - mm) {
                // 如果队首已经超出了长度限制，那么直接弹出并从答案中减去队首的答案
                sub(cur, q.front().ans);
                q.pop_front();
            } else if (i > mm) {
                // 如果队首没有超出限制，但是由于 i 向前移动导致队首向前延伸受到影响，那么应该将队首答案减去队首高度
                int t = q.front().val;
                sub(q.front().ans, t);
                sub(cur, t);
            }
        }
        // 最后将当前位置的信息入队
        int tmp = sum[i] * (q.empty() ? min(i, mm) : (i - q.back().id)) % kMod;
        q.push(sum[i], i, tmp);
        add(cur, tmp);
        add(ans, cur);
    }
    return ans;
}
int main() {
    scanf("%d%d%d%d", &n, &m, &nn, &mm);
    swap(n, m);
    swap(nn, mm);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            sum[i][j] = (x == 0) ? 0 : sum[i - 1][j] + 1; // sum[i][j] 记录了 (i, j) 位置向上的最大高度
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        add(ans, solve(sum[i])); // 将矩形右下角限制在第 i 行
    }
    printf("%d\n", ans);
    return 0;
}