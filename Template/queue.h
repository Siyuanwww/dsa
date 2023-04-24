template <typename T, const int kN>
class Queue {
private:
    int head_, tail_;
    T q_[kN];
public:
    Queue() : head_(0), tail_(0) {}
    bool empty() const {
        return head_ == tail_;
    }
    int size() const {
        return tail_ - head_;
    }
    T &operator[](int x) const {
        return x >= 0 ? q_[head_ + x] : q_[tail_ + x];
    }
    T &front() const {
        return q_[head_];
    }
    T &back() const {
        return q_[tail - 1];
    }
    void Clear() {
        head_ = tail_ = 0;
    }
    T PushFront(const T &x) {
        return q_[--head_] = x;
    }
    T PushBack(const T &x) {
        return q_[tail_++] = x;
    }
    T PopFront() {
        return q_[head_++];
    }
    T PopBack() {
        return q_[--tail_];
    }
};