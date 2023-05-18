template <typename T>
struct Node {
    T data;
    Node<T> *pred, *succ;
    Node(T data = T(), Node<T> *pred = nullptr, Node<T> *succ = nullptr) : data(data), pred(pred), succ(succ) {}
    Node<T> *InsertPred(const T &data) {
        Node<T> *p = new Node<T>(data, pred, this);
        pred->succ = p;
        pred = p;
        return p;
    }
    Node<T> *InsertPred(Node<T> *p) {
        p->pred = pred;
        p->succ = this;
        pred->succ = p;
        pred = p;
        return p;
    }
};

template <typename T>
class List {
private:
    Node<T> *head, *tail;
    int size;
public:
    List() : head(new Node<T>()), tail(new Node<T>()), size(0) {
        head->succ = tail;
        tail->pred = head;
    }
    bool Empty() const {
        return size == 0;
    }
    int Size() const {
        return size;
    }
    Node<T> *&Begin() const {
        return head->succ;
    }
    Node<T> *&End() const {
        return tail;
    }
    T Front() const {
        return head->succ->data;
    }
    T Back() const {
        return tail->pred->data;
    }
    Node<T> *&operator[](int x) const {
        Node<T> *p = head->succ;
        for (; x--; p = p->succ);
        return p;
    }
    Node<T> *Insert(const T &data, int x) {
        size++;
        return this->operator[](x)->InsertPred(data);
    }
    Node<T> *Insert(Node<T> *p, int x) {
        size++;
        return this->operator[](x)->InsertPred(p);
    }
    Node<T> *PushBack(const T &data) {
        size++;
        return tail->InsertPred(data);
    }
    Node<T> *PushBack(Node<T> *p) {
        size++;
        return tail->InsertPred(p);
    }
    Node<T> *PushFront(const T &data) {
        size++;
        return head->succ->InsertPred(data);
    }
    Node<T> *PushFront(Node<T> *p) {
        size++;
        return head->succ->InsertPred(p);
    }
    T PopBack() {
        size--;
        return remove(tail->pred);
    }
    T PopFront() {
        size--;
        return remove(head->succ);
    }
    Node<T> *Find(const T &data) {
        Node<T> *p = head->succ;
        for (; p != tail; p = p->succ) {
            if (p->data == data) {
                return p;
            }
        }
        return tail;
    }
    T Pop(Node<T> *p) {
        size--;
        T tmp = p->data;
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        return tmp;
    }
    T Erase(Node<T> *p) {
        T tmp = pop(p);
        delete p;
        return tmp;
    }
    T Pop(int x) {
        return pop(this->operator[](x));
    }
    T Erase(int x) {
        return erase(this->operator[](x));
    }
    void Swap(int x, int y) {
        if (x == y) {
            return;
        }
        if (x > y) {
            int t = x;
            x = y;
            y = t;
        }
        Node<T> *p = this->operator[](x);
        Node<T> *q = this->operator[](y);
        auto link = [](Node<T> *x, Node<T> *y) {
            x->succ = y;
            y->succ = x;
        };
        if (x + 1 == y) {
            Node<T> *u = p->pred, *v = q->succ;
            link(u, q);
            link(q, p);
            link(p, v);
        } else {
            Node<T> *p1 = p->pred, *p2 = q->pred, *s1 = p->succ, *s2 = q->succ;
            link(p1, q);
            link(q, s1);
            link(p2, p);
            link(p, s2);
        }
    }
};