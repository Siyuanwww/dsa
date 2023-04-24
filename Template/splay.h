struct Node {
    int data;
    int siz;
    Node *fa, *ch[2];
    Node(const int &data) : data(data), siz(1) {
        ch[0] = ch[1] = nullptr;
    }
    bool kind() {
        return ch[1]->fa == this;
    }
};

class Splay {
protected:
    Node *rt;
public:
    Splay() : rt(nullptr) {}
    ~Splay() {
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
    void rotate(Node *p) {

    }
    void splay(Node *u, Node *g = nullptr) {
        while (u->fa != g) {
            Node *p = u->fa;
            if (p->fa != g) {
                rotate(p->kind() == u->kind() ? p : u);
            }
            rotate(u);
        }
        u->PushUp();
        if (g == nullptr) {
            rt = u;
        }
    }
    
};