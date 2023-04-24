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
        return tmp;
    }
    T remove(int x) {
        _size--;
        return remove(this->operator[](x));
    }
    void swap(int x, int y) {
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

// todo: erase & pop