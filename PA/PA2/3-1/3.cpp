#include <cstdio>

const int kN = 1e6 + 5;

struct Node {
    int id;
    Node *nxt;
    Node(int id = 0) : id(id), nxt(nullptr) {}
};

struct List {
    Node *head, *tail;
    List() : head(nullptr), tail(nullptr) {}
    void insert(int x) {
        if (head == nullptr) {
            head = tail = new Node(x);
        } else {
            tail->nxt = new Node(x);
            tail = tail->nxt;
        }
    }
} a[kN];

struct Queue {
    int a[kN], head, tail;
    Queue() : head(0), tail(0) {}
    bool empty() {
        return head == tail;
    }
    void push(int x) {
        a[tail++] = x;
    }
    void pop() {
        head++;
    }
    int front() {
        return a[head];
    }
} q;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int m;
        scanf("%d", &m);
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            a[i].insert(x);
        }
    }
    q.push(1);
    for (; !q.empty(); ) {
        int u = q.front();
        printf("%d\n", u);
        q.pop();
        for (Node *p = a[u].head; p != nullptr; p = p->nxt) {
            q.push(p->id);
        }
    }
    return 0;
}