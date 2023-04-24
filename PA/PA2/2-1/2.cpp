#include <cstdio>

const int kN = 2e6 + 5;
bool vis[kN];
int a[kN][2];
struct Queue {
    int a[kN], head, tail, size;
    bool empty() {
        return size == 0;
    }
    void push(int x) {
        a[tail++] = x;
    }
    int front() {
        for (; !vis[a[head]]; head++);
        return a[head];
    }
} q[3];

void put(int x, int y, int id) {
    vis[id] = true;
    q[x].push(id);
    q[y].push(id);
    q[x].size++;
    q[y].size++;
    a[id][0] = x;
    a[id][1] = y;
}
int use(int x) {
    if (q[x].empty()) {
        return -1;
    }
    int id = q[x].front();
    vis[id] = false;
    q[a[id][0]].size--;
    q[a[id][1]].size--;
    return id;
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        put(x, y, i);
    }
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 0) {
            int x, y;
            scanf("%d%d", &x, &y);
            put(x, y, ++n);
        } else {
            int x;
            scanf("%d", &x);
            printf("%d\n", use(x));
        }
    }
    return 0;
}