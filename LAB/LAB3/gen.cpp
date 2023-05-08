#include <bits/stdc++.h>

struct Info {
    int id, accepted, submited;
    std::string name;
};
int main(int argv, char *argc[]) {
    freopen("./dataset/poj.txt", "r", stdin);
    freopen("./poj.in", "w", stdout);
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::vector<Info> dataset;
    int _a, _c, _d;
    std::string _b;
    for (; std::cin >> _a >> _b >> _c >> _d; dataset.emplace_back(Info{_a, _c, _d, _b}));
    int n = std::atoi(argc[1]), m = std::atoi(argc[2]);
    std::shuffle(dataset.begin(), dataset.end(), rng);
    for (int i = 0; i < n; i++) {
        printf("0 %s %d\n", dataset[i].name.c_str(), dataset[i].accepted);
    }
    std::shuffle(dataset.begin(), dataset.end(), rng);
    for (int i = 0; i < m; i++) {
        printf("1 %s\n", dataset[i].name.c_str());
    }
    printf("2\n");
    return 0;
}