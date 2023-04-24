#include <bits/stdc++.h>
#include <chrono>

int main() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int n = 500000;
    int size = 0;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) {
        int opt = std::uniform_int_distribution<int>(1, i < n / 100 ? 1 : 10)(rng);
        if (opt <= 6) {
            printf("%d %d %d\n", 1, std::uniform_int_distribution<int>(0, size)(rng), std::uniform_int_distribution<int>(0, INT_MAX)(rng));
            size++;
        } else if (opt <= 8) {
            printf("%d %d %d\n", 2, std::uniform_int_distribution<int>(0, size - 1)(rng), 0);
            size--;
        } else {
            printf("%d %d %d\n", 3, std::uniform_int_distribution<int>(0, size - 1)(rng), 0);
        }
    }
    return 0;
}