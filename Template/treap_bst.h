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
    Node *ch[2];
    Node(const int &val = 0) : val(val), size(1), key(rand()) {
        ch[0] = ch[1] = null;
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
    void SplitVal(Node *p, int val, Node *&x, Node *&y) {
        if (p == null) {
            x = y = null;
            return;
        }
        if (val >= p->val) {
            x = p;
            SplitVal(p->ch[1], val, p->ch[1], y);
        } else {
            y = p;
            SplitVal(p->ch[0], val, x, p->ch[0]);
        }
        p->PushUp();
    }
    void SplitSiz(Node *p, int k, Node *&x, Node *&y) {
        if (p == null) {
            x = y = null;
            return;
        }
        int size = p->ch[0]->size;
        if (k > size) {
            x = p;
            SplitSiz(p->ch[1], k - size, p->ch[1], y);
        } else {
            y = p;
            SplitSiz(p->ch[0], k, x, p->ch[0]);
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
    void Insert(int val) {
        Node *x, *y;
        SplitVal(rt, val, x, y);
        rt = Merge(Merge(x, new Node(val)), y);
    }
    bool Erase(int val) {
        Node *x, *y, *z;
        SplitVal(rt, val - 1, x, y);
        SplitSiz(y, 1, y, z);
        if (y != null && y->val == val) {
            delete y;
            rt = Merge(x, z);
            return true;
        } else {
            rt = Merge(Merge(x, y), z);
            return false;
        }
    }
    int EraseAll(int val) {
        Node *x, *y, *z;
        SplitVal(rt, val - 1, x, y);
        SplitVal(y, val, y, z);
        int cnt = y->size;
        if (y != null) {
            delete y;
        }
        rt = Merge(x, z);
        return cnt;
    }
    int Kth(int k) {
        Node *x, *y, *z;
        SplitSiz(rt, k - 1, x, y);
        SplitSiz(y, 1, y, z);
        int val = y->val;
        rt = Merge(Merge(x, y), z);
        return val;
    }
    int Rank(int val) {
        Node *x, *y;
        SplitVal(rt, val - 1, x, y);
        int rank = x->size + 1;
        rt = Merge(x, y);
        return rank;
    }
    int Pred(int val) {
        Node *x, *y, *z;
        SplitVal(rt, val - 1, y, z);
        if (y == null) {
            rt = Merge(y, z);
            return val;
        }
        SplitSiz(y, y->size - 1, x, y);
        int pred = y->val;
        rt = Merge(Merge(x, y), z);
        return pred;
    }
    int Succ(int val) {
        Node *x, *y, *z;
        SplitVal(rt, val, x, y);
        if (y == null) {
            rt = Merge(x, y);
            return val;
        }
        SplitSiz(y, 1, y, z);
        int succ = y->val;
        rt = Merge(Merge(x, y), z);
        return succ;
    }
};