template <typename T>
struct Node {
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
    Node<T> *head_, *tail_;
    int size_;
public:
    List() : head_(new Node<T>()), tail_(new Node<T>()), size_(0) {
        head_->succ = tail_;
        tail_->pred = head_;
    }
    bool empty() const {
        return size_ == 0;
    }
    int size() const {
        return size_;
    }
    Node<T> *&begin() const {
        return head_->succ;
    }
    Node<T> *&end() const {
        return tail_;
    }
    Node<T> *&operator[](int x) const {
        Node<T> *p = head_->succ;
        for (; x--; p = p->succ);
        return p;
    }
    Node<T> *Insert(const T &data, int x) {
        size_++;
        return this->operator[](x)->insertPred(data);
    }
    Node<T> *Insert(Node<T> *p, int x) {
        size_++;
        return this->operator[](x)->insertPred(p);
    }
    Node<T> *PushBack(const T &data) {
        size_++;
        return tail_->insertPred(data);
    }
    Node<T> *PushBack(Node<T> *p) {
        size_++;
        return tail_->insertPred(p);
    }
    Node<T> *PushFront(const T &data) {
        size_++;
        return head_->succ->insertPred(data);
    }
    Node<T> *PushFront(Node<T> *p) {
        size_++;
        return head_->succ->insertPred(p);
    }
    T PopBack() {
        size_--;
        return remove(tail_->pred);
    }
    T PopFront() {
        size_--;
        return remove(head_->succ);
    }
    Node<T> *Find(const T &data) {
        Node<T> *p = head_->succ;
        for (; p != tail_; p = p->succ) {
            if (p->data == data) {
                return p;
            }
        }
        return tail_;
    }
    T Pop(Node<T> *p) {
        size_--;
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