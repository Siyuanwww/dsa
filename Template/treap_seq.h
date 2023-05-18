#include <cstdlib>

template <typename T>
inline void swap(T &x, T &y) {
    T t = static_cast<T&&>(x);
    x = static_cast<T&&>(y);
    y = static_cast<T&&>(t);
}
struct Node *null;
struct Node {
    int val;
    int size, key;
    bool rev;
    Node *ch[2];
    Node(const int &val = 0) : val(val), size(1), key(rand()), rev(false) {
        ch[0] = ch[1] = null;
    }
    void Reverse() {
        rev ^= 1;
        swap(ch[0], ch[1]);
    }
    void PushDown() {
        if (rev) {
            if (ch[0] != null) {
                ch[0]->Reverse();
            }
            if (ch[1] != null) {
                ch[1]->Reverse();
            }
            rev = false;
        }
    }
    void PushUp() {
        size = ch[0]->size + ch[1]->size + 1;
    }
};

class Treap {
protected:
    Node *rt;
    void Deconstruct(Node *p) {
        if (p == null) {
            return;
        }
        Deconstruct(p->ch[0]);
        Deconstruct(p->ch[1]);
        delete p;
    }
    void Split(Node *p, int k, Node *&x, Node *&y) {
        if (p == null) {
            x = y = null;
            return;
        }
        p->PushDown();
        int size = p->ch[0]->size;
        if (k > size) {
            x = p;
            Split(p->ch[1], k - size, p->ch[1], y);
        } else {
            y = p;
            Split(p->ch[0], k, x, p->ch[0]);
        }
        p->PushUp();
    }
    Node *Merge(Node *x, Node *y) {
        if (x == null) {
            return y;
        }
        if (y == null) {
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
public:
    Treap() {
        null = new Node();
        null->ch[0] = null->ch[1] = null;
        null->size = 0;
        rt = null;
    }
    ~Treap() {
        Deconstruct(rt);
    }
    void Insert(int k, int val) {
        Node *x, *y;
        Split(rt, k, x, y);
        rt = Merge(Merge(x, new Node(val)), y);
    }
    void Erase(int k) {
        Node *x, *y, *z;
        Split(rt, k, x, y);
        Split(y, 1, y, z);
        rt = Merge(x, z);
    }
    int operator[](int k) {
        Node *x, *y, *z;
        Split(rt, k, x, y);
        Split(y, 1, y, z);
        int val = y->val;
        rt = Merge(Merge(x, y), z);
        return val;
    }
    void Reverse(int l, int r) {
        Node *x, *y, *z;
        Split(rt, r, y, z);
        Split(y, l - 1, x, y);
        y->Reverse();
        rt = Merge(Merge(x, y), z);
    }
};