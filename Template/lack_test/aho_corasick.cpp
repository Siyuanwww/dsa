#include <cstdio>
#include <cstring>

const int kN = 1e3 + 5, kM = 1e4 + 5;
int n, m, p;
char str[kM][kN];

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
Queue<int, kN * kM * 2> q;
template <int kN, int kS>
class AhoCorasick {
private:
    int siz, ch[kN][kS], fail[kN], bel[kN];
    AhoCorasick() {
        Clear();
    }
public:
    void Clear() {
        siz = 0;
        NewNode();
    }
    int NewNode() {
        for (int i = 0; i < kN; i++) {
            ch[siz][i] = -1;
        }
        fail[siz] = -1;
        bel[siz] = 0;
        return siz++;
    }
    void Insert(char *str, int n, int id) {
        int u = 0;
        for (int i = 0; i < n; i++) {
            int c = str[i] - 'a';
            if (ch[u][c] < 0) {
                ch[u][c] = NewNode();
            }
            u = ch[u][c];
        }
        bel[u] = id;
    }
    void Build() {
        for (int i = 0; i < kS; i++) {
            if (ch[0][i] >= 0) {
                q.PushBack(ch[0][i]);
                fail[ch[0][i]] = 0;
            }
        }
        while (!q.Empty()) {
            int u = q.Front();
            for (int i = 0; i < kS; i++) {
                if (ch[u][i] >= 0) {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    q.PushBack(ch[u][i]);
                } else {
                    ch[u][i] = ch[fail[u]][i];
                }
            }
        }
    }
    int Query(char *str, int n) {
        int u = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            int c = str[i] - 'a';
            for (; u > 0 && ch[u][c] < 0; u = fail[u]);
            if (ch[u][c] >= 0) {
                u = ch[u][c];   
            }
            if (bel[u] > 0) {
                ans++;
                bel[u] = 0;
            }
        }
        return ans;
    }
};