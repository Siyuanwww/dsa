#include <cstdio>
#include <cstdlib>
#include <cassert>

const int kN = 1.1e6 + 5;
int n, m, on[kN], seq[kN];
struct Process {
    int pid, rank, create, running, stamp;
    bool operator>(const Process &r) const {
        return rank != r.rank ? rank > r.rank : create != r.create ? create < r.create : pid < r.pid;
    }
} p[kN];
struct Operation {
    int t, type, id, rank;
} q[kN];
template <class T>
void swap(T &x, T &y) {
    T t = x;
    x = y;
    y = t;
}
// 使用堆实时维护当前的进程集合
// 修改优先级时，使用惰性修改，即不在原有的进程上直接修改，而是加入一个新的进程，并打上时间戳
class Heap {
private:
    int n;
    struct Node {
        int id, stamp;
        bool operator>(const Node &r) const {
            return p[id] > p[r.id];
        }
    } a[kN];
    void Up(int x) {
        for (; x > 1 && a[x] > a[x >> 1]; swap(a[x], a[x >> 1]), x >>= 1);
    }
    void Down(int x) {
        while (x * 2 <= n) {
            int t = x * 2;
            if (t + 1 <= n && a[t + 1] > a[t]) {
                t++;
            }
            if (a[x] > a[t]) {
                break;
            }
            swap(a[x], a[t]);
            x = t;
        }
    }
public:
    bool empty() {
        return n == 0;
    }
    void Insert(const Node &p) {
        a[++n] = p;
        Up(n);
    }
    void Pop() {
        swap(a[1], a[n--]);
        Down(1);
    }
    int Top() {
        return a[1].id;
    }
    void Fix() {
        for (; !empty() && a[1].stamp != p[a[1].id].stamp; Pop());
    }
};
Heap H;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &p[i].pid, &p[i].rank, &p[i].create, &p[i].running);
        seq[p[i].pid] = i;
        // q[i] = Operation{p[i].create, 0, i, 0};
    }
    int j = 1, k = 0;
    for (int i = 1; i <= m; i++) {
        int pid, t, rank;
        scanf("%d%d%d", &pid, &t, &rank);
        for (; j <= n && p[j].create <= t; q[++k] = Operation{p[j].create, 0, seq[p[j].pid], 0}, j++);
        q[++k] = Operation{t, 1, seq[pid], rank};
    }
    for (; j <= n; q[++k] = Operation{p[j].create, 0, seq[p[j].pid], 0}, j++);
    q[++k] = Operation{2147483647, 1, 0, 0};
    int cnt = 0;
    for (int i = 1; i <= n + m; ) {
        int j = i;
        for (; j <= n + m && q[j].t == q[i].t; j++) { // 进行当前时间的操作序列
            if (q[j].type == 0) {
                on[q[j].id] = true;
                H.Insert({q[j].id, 0});
            } else if (on[q[j].id]) {
                p[q[j].id].stamp = j;
                p[q[j].id].rank = q[j].rank;
                H.Insert({q[j].id, j});
            }
        }
        i = j;
        int d = q[i].t - q[i - 1].t, cur = q[i - 1].t;
        H.Fix();
        while (!H.empty()) { // 处理时间间隔内的进程
            int id = H.Top();
            if (d >= p[id].running) {
                H.Pop();
                cur += p[id].running;
                d -= p[id].running;
                printf("%d %d\n", p[id].pid, cur);
                cnt++;
                on[id] = false;
            } else {
                p[id].running -= d;
                break;
            }
            H.Fix();
        }
    }
    return 0;
}