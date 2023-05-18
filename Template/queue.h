template <typename T, const int kN>
class Queue {
private:
    int head, tail;
    T que[kN];
public:
    Queue() : head(0), tail(0) {}
    bool Empty() const {
        return head == tail;
    }
    int Size() const {
        return tail - head;
    }
    T &operator[](int x) const {
        return x >= 0 ? que[head + x] : que[tail + x];
    }
    T &Front() const {
        return que[head];
    }
    T &Back() const {
        return que[tail - 1];
    }
    void Clear() {
        head = tail = 0;
    }
    T PushFront(const T &x) {
        return que[--head] = x;
    }
    T PushBack(const T &x) {
        return que[tail++] = x;
    }
    T PopFront() {
        return que[head++];
    }
    T PopBack() {
        return que[--tail];
    }
};