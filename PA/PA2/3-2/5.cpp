#include <cstdio>

const int kN = 1e6 + 5;

template <typename T>
class Node {
public:
    T data;
    Node<T> *pred, *succ;
    Node(T data = T(), Node<T> *pred = nullptr, Node<T> *succ = nullptr) : data(data), pred(pred), succ(succ) {}
    Node<T> *insertPred(const T &data) {
        Node *p = new Node<T>(data, pred, this);
        pred->succ = p;
        pred = p;
        return p;
    }
};

// 实现了一个常规的链表结构
template <typename T>
class List {
private:
    Node<T> *head, *tail;
    int _size;
public:
    List() : head(new Node<T>()), tail(new Node<T>()), _size(0) {
        head->succ = tail;
        tail->pred = head;
    }
    bool empty() const {
        return _size == 0;
    }
    int size() const {
        return _size;
    }
    Node<T> *&begin() {
        return head->succ;
    }
    Node<T> *&end() {
        return tail;
    }
    Node<T> *operator[](int x) const {
        Node<T> *p = head->succ;
        for (; x--; p = p->succ);
        return p;
    }
    Node<T> *insert(const T &data, int x) {
        _size++;
        return this->operator[](x)->insertPred(data);
    }
    Node<T> *push(const T &data) {
        _size++;
        return tail->insertPred(data);
    }
    Node<T> *find(const T &data) {
        Node<T> *p = head->succ;
        for (; p != tail; p = p->succ) {
            if (p->data == data) {
                return p;
            }
        }
        return tail;
    }
    T remove(Node<T> *p) {
        _size--;
        T tmp = p->data;
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        delete p;
        return tmp;
    }
    T remove(int x) {
        _size--;
        return remove(this->operator[](x));
    }
};

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

List<int> e[kN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int s, x;
        scanf("%d", &s);
        while (s--) {
            scanf("%d", &x);
            e[i].push(x);
        }
    }
    while (m--) {
        int s, x;
        scanf("%d", &s);
        int p = 0, u = 1;
        bool flg = true;
        while (s--) {
            scanf("%d", &x);
            if (flg) { // 向下查找时判断是否合法
                x < e[u].size() ? (u = e[p = u][x]->data) : (flg = false);
            }
        }
        e[p].remove(e[p].find(u));
        scanf("%d", &s);
        int v = 1;
        flg = true;
        while (s--) {
            scanf("%d", &x);
            if (flg) {
                x < e[v].size() ? (v = e[v][x]->data) : (flg = false);
            }
        }
        scanf("%d", &x);
        e[v].insert(u, x);
    }
    // 使用经典的 BFS 算法输出层次遍历结果
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        printf("%d\n", u);
        q.pop();
        for (Node<int> *p = e[u].begin(); p != e[u].end(); p = p->succ) {
            q.push(p->data);
        }
    }
    return 0;
}