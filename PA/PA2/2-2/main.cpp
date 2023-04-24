#include <cstdio>

const int kN = 2e3 + 5, kMod = 10007;
int n, m, nn, mm, sum[kN][kN];
struct Info {
    int val, id, ans;
};
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
        for (; !q.empty() && q.back().val > sum[i]; ) {
            sub(cur, q.back().ans);
            q.pop_back();
        }
        if (!q.empty()) {
            if (q.front().id == i - mm) {
                sub(cur, q.front().ans);
                q.pop_front();
            } else if (i > mm) {
                int t = q.front().val;
                sub(q.front().ans, t);
                sub(cur, t);
            }
        }
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
            sum[i][j] = (x == 0) ? 0 : sum[i - 1][j] + 1;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        add(ans, solve(sum[i]));
    }
    printf("%d\n", ans);
    return 0;
}