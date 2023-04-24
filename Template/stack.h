template <typename T, const int kN>
class Stack {
private:
    int size_;
    T s_[kN];
public:
    Stack() : size_(0) {}
    bool empty() const {
        return size_ == 0;
    }
    int size() const {
        return size_;
    }
    T &top() const {
        return s_[size_ - 1];
    }
    void Clear() {
        size_ = 0;
    }
    T Push(const T &x) {
        return s_[size_++] = x;
    }
    T Pop() {
        return s_[--size_];
    }
};