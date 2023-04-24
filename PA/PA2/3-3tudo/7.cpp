#include <cstdio>
#include <cstring>

template <typename T>
class Node {
public:
    T data;
    Node<T> *pred, *succ;
    Node(T data = T(), Node<T> *pred = nullptr, Node<T> *succ = nullptr) : data(data), pred(pred), succ(succ) {}
    Node<T> *insertPred(const T &data) {
        Node<T> *p = new Node<T>(data, pred, this);
        pred->succ = p;
        pred = p;
        return p;
    }
    Node<T> *insertPred(Node<T> *p) {
        p->pred = pred;
        p->succ = this;
        pred->succ = p;
        pred = p;
        return p;
    }
};
Node<char> node[14400005];

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
    Node<T> *begin() {
        return head->succ;
    }
    Node<T> *end() {
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
    Node<T> *insert(Node<T> *p, int x) {
        _size++;
        return this->operator[](x)->insertPred(p);
    }
    Node<T> *push_back(const T &data) {
        _size++;
        return tail->insertPred(data);
    }
    Node<T> *push_back(Node<T> *p) {
        _size++;
        return tail->insertPred(p);
    }
    Node<T> *push_front(const T &data) {
        _size++;
        return head->succ->insertPred(data);
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
        delete p;
        return tmp;
    }
    T remove(int x) {
        _size--;
        return remove(this->operator[](x));
    }
};

List<char> a, b;
char str[3200000];

template <typename T>
Node<T> *newNode(const T &data) {
    static int idx = 0;
    node[idx].data = data;
    return node + idx++;
}

int main() {
    scanf("%s", str);
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        a.push_back(newNode(str[i]));
        b.push_front(newNode(str[i]));
    }
    auto al = a.begin(), ar = a.end()->pred;
    auto bl = b.begin()->succ, br = b.end();
    bool rev = false;
    int m;
    scanf("%d", &m);
    while (m--) {
        char opt[2];
        scanf("%s", opt);
        switch (opt[0]) {
            case '<':
                scanf("%s", opt);
                if (opt[0] == 'L') {
                    if (al != a.begin()) {
                        al = al->pred;
                        br = br->succ;
                        printf("T\n");
                    } else {
                        printf("F\n");
                    }
                } else {
                    if (ar != a.begin()) {
                        ar = ar->pred;
                        bl = bl->succ;
                        printf("T\n");
                    } else {
                        printf("F\n");
                    }
                }
                break;
            case '>':
                scanf("%s", opt);
                if (opt[0] == 'L') {
                    if (al != a.end()->pred) {
                        al = al->succ;
                        br = br->pred;
                        printf("T\n");
                    } else {
                        printf("F\n");
                    }
                } else {
                    if (ar != a.end()->pred) {
                        ar = ar->succ;
                        bl = bl->pred;
                        printf("T\n");
                    } else {
                        printf("F\n");
                    }
                }
                break;
            case 'I':
                char ch;
                scanf("%s %c", opt, &ch);
                if (opt[0] == 'L') {
                    a.insert(al->succ, ch);
                    b.insert(br, ch);
                    al = al->succ;
                    br = br->pred;
                } else {

                }
                printf("T\n");
                break;
            case 'D':

            case 'R':
                if (pr - pl > 0) {
                    if (pr - pl > 1) {
                        auto al_t = al->succ, ar_t = ar->succ;
                        auto bl_t = bl->pred, br_t = br->pred;
                        al->succ = bl;
                        bl->pred = al;
                        ar_t->pred = br_t;
                        br_t->succ = ar_t;
                        ar->pred = br;
                        br->succ = ar;
                        al_t->pred = bl_t;
                        bl_t->succ = al_t;
                    }
                    printf("T\n");
                } else {
                    printf("F\n");
                }
                break;
            case 'S':
                int len = 0;
                for (auto p = a.begin(); p != a.end(); p = p->succ) {
                    str[len++] = p->data;
                }
                str[len] = '\0';
                printf("%s\n", str);
                break;
        }
    }

}