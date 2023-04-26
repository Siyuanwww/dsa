struct Node *null;
struct Node {
    int val;
    int siz;
    Node *fa, *ch[2];
    Node(const int &val = 0) : val(val), siz(1) {
        ch[0] = ch[1] = null;
    }
    bool kind() {
        return ch[1]->fa == this;
    }
    void PushUp() {
        siz = ch[0]->siz + ch[1]->siz + 1;
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
        null->siz = 0;
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
        for (; val != u->val && u->ch[val > u->val] != null; ) {
            u = u->ch[val > u->val];
        }
        Splay(u);
    }
    int Count(int val) {

    }
    void Insert(int val) {

    }
    void Erase(int val) {

    }
    void EraseAll(int val) {

    }
    int Prev(int val) {

    }
    int Succ(int val) {

    }
    int operator[](int k) {

    }
    int Rank(int val) {
        
    }
};