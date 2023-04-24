#include <cstdio>
#include <cstdlib>
#include <ctime>

#define SIZE(p) ((p) == nullptr ? 0 : (p)->siz)

int n, m;
template <typename T>
inline void swap(T &x, T &y) {
    T t = x;
    x = y;
    y = t;
}
struct Node {
    int nam, siz, key;
    bool rev;
    Node *ch[2];
    Node(int nam = 0) : nam(nam), siz(1), key(rand()), rev(false) {
        ch[0] = ch[1] = nullptr;
    }
    // 使用懒标记记录翻转操作
    void Reverse() {
        rev ^= 1;
        swap(ch[0], ch[1]);
    }
    void PushDown() {
        if (rev) {
            if (ch[0] != nullptr) {
                ch[0]->Reverse();
            }
            if (ch[1] != nullptr) {
                ch[1]->Reverse();
            }
            rev = false;
        }
    }
    void PushUp() {
        siz = SIZE(ch[0]) + SIZE(ch[1]) + 1;
    }
};

// 实现了一个标准的 FHQTreap（或者称之为非旋 Treap）
// 所有的操作都可以通过 split 和 merge 操作很容易写出
class FHQTreap {
    Node *rt = nullptr;
    void Split(Node *p, int k, Node *&x, Node *&y) {
        if (p == nullptr) {
            x = y = nullptr;
            return;
        }
        p->PushDown();
        int siz = SIZE(p->ch[0]) + 1;
        if (k >= siz) {
            x = p;
            Split(p->ch[1], k - siz, p->ch[1], y);
        } else {
            y = p;
            Split(p->ch[0], k, x, p->ch[0]);
        }
        p->PushUp();
    }
    Node *Merge(Node *x, Node *y) {
        if (x == nullptr) {
            return y;
        }
        if (y == nullptr) {
            return x;
        }
        x->PushDown();
        y->PushDown();
        if (x->key < y->key) {
            x->ch[1] = Merge(x->ch[1], y);
            x->PushUp();
            return x;
        } else {
            y->ch[0] = Merge(x, y->ch[0]);
            y->PushUp();
            return y;
        }
    }
    void Print(Node *p) {
        p->PushDown();
        if (p->ch[0] != nullptr) {
            Print(p->ch[0]);
        }
        printf("%d ", p->nam);
        if (p->ch[1] != nullptr) {
            Print(p->ch[1]);
        }
    }
public:
    void Insert(int k, int nam) {
        Node *x, *y;
        Split(rt, k, x, y);
        rt = Merge(Merge(x, new Node(nam)), y);
    }
    void Swap(int p, int q) {
        if (p == q) {
            return;
        }
        if (p > q) {
            swap(p, q);
        }
        Node *x, *y, *z, *u, *v;
        Split(rt, p + 1, x, y);
        Split(y, q - p, y, z);
        Split(x, x->siz - 1, x, u);
        Split(y, y->siz - 1, y, v);
        rt = Merge(Merge(Merge(Merge(x, v), y), u), z);
    }
    void Shift(int r) {
        r %= rt->siz;
        if (r < 0) {
            r += rt->siz;
        }
        Node *x, *y;
        Split(rt, rt->siz - r, x, y);
        rt = Merge(y, x);
    }
    void Reverse(int p, int q) {
        if (p < q) {
            Node *x, *y, *z;
            Split(rt, q + 1, y, z);
            Split(y, p, x, y);
            y->Reverse();
            rt = Merge(Merge(x, y), z);
        } else if (p > q) {
            Node *x, *y, *z;
            Split(rt, p, y, z);
            Split(y, q + 1, x, y);
            int k = z->siz;
            Node *t = Merge(z, x);
            t->Reverse();
            Split(t, k, z, x);
            rt = Merge(Merge(x, y), z);
        }
    }
    void Print() {
        Print(rt);
        printf("\n");
    }
} T;

int main() {
    srand(time(0));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        char str[5];
        int x, y;
        scanf("%s%d", str, &x);
        switch (str[0]) {
            case 'I':
                scanf("%d", &y);
                T.Insert(y, x);
                break;
            case 'S':
                scanf("%d", &y);
                T.Swap(x, y);
                break;
            case 'R':
                T.Shift(x);
                break;
            case 'F':
                scanf("%d", &y);
                T.Reverse(x, y);
                break;
        }
    }
    T.Print();
    return 0;
}