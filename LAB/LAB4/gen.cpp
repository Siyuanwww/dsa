#include <bits/stdc++.h>

std::string generate(int n, int s = 26) {
    std::string str;
    str.resize(n);
    for (int i = 0; i < n; i++) {
        str[i] = rand() % s + 'a';
    }
    return str;
}
int main() {
    srand(time(0));
    // std::cout << generate(1000000) << '\n';
    // int n = 1000;
    // std::cout << n << '\n';
    // for (int i = 0; i < n; i++) {
    //     std::cout << generate(4) << '\n';
    // }
    // std::cout << generate(1000000) << '\n';
    // int n = 1000;
    // std::cout << n << '\n';
    // for (int i = 0; i < n; i++) {
    //     std::cout << generate(5 + rand() % 11) << '\n';
    // }
    // std::cout << std::string(1000000, 'a') << '\n';
    // int n = 10;
    // std::cout << n << '\n';
    // for (int i = 0; i < n; i++) {
    //     std::cout << std::string(9000, 'a') << generate(800 + rand() % 401) << '\n';
    // }
    // std::string str;
    // str.resize(1000000);
    // for (int i = 0; i < (int)str.size(); i++) {
    //     str[i] = i % 100000 ? 'a' : 'b';
    // }
    // std::cout << str << '\n';
    // int n = 1000;
    // std::cout << n << '\n';
    // for (int i = 0; i < n; i++) {
    //     std::cout << std::string(900 + rand() % 120, 'a') << '\n';
    // }
    std::cout << generate(100000) << '\n';
    int n = 100;
    std::cout << n << '\n';
    for (int i = 0; i < n; i++) {
        std::cout << generate(1000) << '\n';
    }
    return 0;
}