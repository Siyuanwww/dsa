#include <cstdio>
#include <cassert>

const int kN = 1e6 + 5;

inline int max(const int &x, const int &y) {
    return x > y ? x : y;
}
template <typename T>
class Node {
public:
    T data;
    int size, height, suc_max;
    Node<T> *pred, *succ;
    Node(T data = T(), Node<T> *pred = nullptr, Node<T> *succ = nullptr) : data(data), size(1), height(0), suc_max(0), pred(pred), succ(succ) {}
    Node<T> *insertPred(Node<T> *p) {
        p->pred = pred;
        p->succ = this;
        pred->succ = p;
        pred = p;
        return p;
    }
};
Node<int> *node[kN];

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
    Node<T> *insert(Node<T> *p, int x) {
        _size++;
        return this->operator[](x)->insertPred(p);
    }
    Node<T> *push_back(Node<T> *p) {
        _size++;
        return tail->insertPred(p);
    }
    Node<T> *push_front(Node<T> *p) {
        _size++;
        return head->succ->insertPred(p);
    }
    T pop_back() {
        _size--;
        return remove(tail->pred);
    }
    T pop_front() {
        _size--;
        return remove(head->succ);
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
        return tmp;
    }
    T remove(int x) {
        _size--;
        return remove(this->operator[](x));
    }
};

List<int> e[kN];
int fa[kN];


template <typename T>
void maintain(Node<T> *p) {
    int tmp = p->succ == nullptr ? 0 : p->succ->suc_max;
    for (; p != nullptr; p = p->pred) {
        p->suc_max = max(p->height, tmp);
        tmp = p->suc_max;
    }
}
void dfs(int u) {
    node[u]->size = 1;
    for (Node<int> *p = e[u].begin(); p != e[u].end(); p = p->succ) {
        dfs(p->data);
        node[u]->size += node[p->data]->size;
    }
    maintain(e[u].end());
    node[u]->height = e[u].begin()->suc_max + 1;
}
void update(int u, int w) {
    if (fa[u] > 0) {
        node[fa[u]]->size += w;
        maintain(e[fa[u]].find(u));
        node[u]->height = e[u].begin()->suc_max + 1;
        update(fa[u], w);
    }
}
void modify() {
    int s, x;
    scanf("%d", &s);
    int u = 1;
    bool flg = true;
    while (s--) {
        scanf("%d", &x);
        if (flg) {
            x < e[u].size() ? (u = e[u][x]->data) : (flg = false);
        }
    }
    e[fa[u]].remove(node[u]);
    maintain(node[u]->pred);
    node[fa[u]]->height = e[u].begin()->suc_max + 1;
    node[fa[u]]->size -= node[u]->size;
    update(fa[u], -node[u]->size);
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
    e[v].insert(node[u], x);
    fa[u] = v;
    update(u, node[u]->size);
}
int queryHeight() {
    int s, x, u = 1;
    scanf("%d", &s);
    bool flg = true;
    while (s--) {
        scanf("%d", &x);
        if (flg) {
            x < e[u].size() ? (u = e[u][x]->data) : (flg = false);
        }
    }
    return node[u]->height;
}
int querySize() {
    int s, x, u = 1;
    scanf("%d", &s);
    bool flg = true;
    while (s--) {
        scanf("%d", &x);
        if (flg) {
            x < e[u].size() ? (u = e[u][x]->data) : (flg = false);
        }
    }
    return node[u]->size;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        node[i] = new Node<int>(i);
    }
    for (int i = 1; i <= n; i++) {
        int s, x;
        scanf("%d", &s);
        while (s--) {
            scanf("%d", &x);
            fa[x] = i;
            e[i].push_back(node[x]);
        }
    }
    dfs(1);
    while (m--) {
        int opt;
        scanf("%d", &opt);
        switch (opt) {
            case 0:
                modify();
                break;
            case 1:
                printf("%d\n", queryHeight());
                break;
            case 2:
                printf("%d\n", querySize());
                break;
        }
        assert(node[1]->size == n);
    }
    return 0;
}