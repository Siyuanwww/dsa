struct Node *null;
struct Node {
    int val;
    int size, cnt;
    Node *fa, *ch[2];
    Node(const int &val = 0) : val(val), size(1), cnt(1) {
        ch[0] = ch[1] = null;
    }
    bool kind() {
        return ch[1]->fa == this;
    }
    void PushUp() {
        size = ch[0]->size + ch[1]->size + cnt;
    }
};

class SplayTree {
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
    void Rotate(Node *x) {
        Node *y = x->fa, *z = y->fa;
        bool k = x->kind();
        x->fa = z;
        if (z != null) {
            z->ch[y->kind()] = x;
        }
        y->ch[k] = x->ch[!k];
        x->ch[!k]->fa = y;
        y->fa = x;
        x->ch[!k] = y;
        y->PushUp();
    }
    void Splay(Node *u, Node *g = null) {
        while (u->fa != g) {
            Node *p = u->fa;
            if (p->fa != g) {
                Rotate(p->kind() == u->kind() ? p : u);
            }
            Rotate(u);
        }
        u->PushUp();
        if (g == null) {
            rt = u;
        }
    }
public:
    SplayTree() {
        null = new Node();
        null->fa = null->ch[0] = null->ch[1] = null;
        null->size = 0;
        rt = null;
    }
    ~SplayTree() {
        Deconstruct(rt);
    }
    void Find(int val) {
        if (rt == null) {
            return;
        }
        Node *u = rt;
        while (val != u->val && u->ch[val > u->val] != null) {
            u = u->ch[val > u->val];
        }
        Splay(u);
    }
    int Count(int val) {
        if (rt == null) {
            return;
        }
        Node *u = rt;
        while (u->val != val && u->ch[val > u->val] != null) {
            u = u->ch[val > u->val];
        }
        Splay(u);
        return rt->val == val ? rt->cnt : 0;
    }
    void Insert(int val) {
        Node *u = rt, *p = null;
        while (u->val != val && u != null) {
            p = u;
            u = u->ch[val > u->val];
        }
        if (u != null) {
            u->cnt++;
        } else {
            u = new Node(val);
            if (p != null) {
                p->ch[val > p->val] = u;
                u->fa = p;
            }
        }
        Splay(u);
    }
    void Erase(int val) {
        Node *u = Prev(val), *v = Succ(val);
        Splay(u);
        Splay(v, u);
        u = v->ch[0];
        if (u == null) {
            return;
        }
        if (u->cnt > 1) {
            u->cnt--;
        } else {
            delete u;
            v->ch[0] = null;
        }
    }
    void EraseAll(int val) {
        Node *u = Prev(val), *v = Succ(val);
        Splay(u);
        Splay(v, u);
        if (v->ch[0] != null) {
            delete v->ch[0];
            v->ch[0] = null;
        }
    }
    Node *Prev(int val) {
        Find(val);
        if (rt->val < val) {
            return rt;
        }
        Node *u = rt->ch[0];
        while (u->ch[1] != null) {
            u = u->ch[1];
        }
        return rt;
    }
    Node *Succ(int val) {
        Find(val);
        if (rt->val > val) {
            return rt;
        }
        Node *u = rt->ch[1];
        while (u->ch[0] != null) {
            u = u->ch[0];
        }
        return rt;
    }
    int operator[](int k) {
        Node *u = rt;
        while (true) {
            if (k <= u->ch[0]->size) {
                u = u->ch[0];
            } else if (k > u->ch[0]->size + u->cnt) {
                k -= u->ch[0]->size + u->cnt;
                u = u->ch[1];
            } else {
                return u->val;
            }
        }
        return 0;
    }
    int Rank(int val) {
        Find(val);
        return rt->ch[0]->size + 1;
    }
};