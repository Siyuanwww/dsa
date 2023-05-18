template <typename T, const int kN>
class Stack {
private:
    int size;
    T stk[kN];
public:
    Stack() : size(0) {}
    bool Empty() const {
        return size == 0;
    }
    int Size() const {
        return size;
    }
    T &Top() const {
        return stk[size - 1];
    }
    void Clear() {
        size = 0;
    }
    T Push(const T &x) {
        return stk[size++] = x;
    }
    T Pop() {
        return stk[--size];
    }
};