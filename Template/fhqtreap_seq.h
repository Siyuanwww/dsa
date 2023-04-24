#include <cstdlib>
#include <algorithm>

#define SIZE(p) ((p) == nullptr ? 0 : (p)->siz)

template <typename T>
inline void swap(T &x, T &y) {
    T t = static_cast<T&&>(x);
    x = static_cast<T&&>(y);
    y = static_cast<T&&>(t);
}
struct Node {
    int data;
    int siz, key;
    bool rev;
    Node *ch[2];
    Node(const int &data) : data(data), siz(1), key(rand()), rev(false) {
        ch[0] = ch[1] = nullptr;
    }
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

class FHQTreap {
    Node *rt;
    FHQTreap() : rt(nullptr) {}
    ~FHQTreap() {
        Deconstruct(rt);
    }
    void Deconstruct(Node *p) {
        if (p == nullptr) {
            return;
        }
        Deconstruct(p->ch[0]);
        Deconstruct(p->ch[1]);
        delete p;
    }
    void Split(Node *p, int k, Node *&x, Node *&y) {
        if (p == nullptr) {
            x = y = nullptr;
            return;
        }
        p->PushDown();
        int siz = SIZE(p->ch[0]);
        if (k > siz) {
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
public:
};

#undef SIZE