#include <bits/stdc++.h>

struct Info {
    int id, accepted, submited;
    std::string name;
};
void read(std::vector<Info> &dataset) {
    int _a, _c, _d;
    std::string _b;
    for (; std::cin >> _a >> _b >> _c >> _d; dataset.emplace_back(Info{_a, _c, _d, _b}));
}
int main(int argv, char *argc[]) {
    freopen("../dataset/poj.txt", "r", stdin);
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::vector<Info> dataset;
    read(dataset);
    int n = 1e5, m = 1e5;
    std::string file(argc[1]);
    double alp = std::atof(argc[2]); // 1, 0.5, 0
    int siz = (int)m * alp;
    std::shuffle(dataset.begin(), dataset.end(), rng);
    std::vector<Info> ins(dataset.begin(), dataset.begin() + n);
    std::vector<Info> que(dataset.end() - (m - siz), dataset.end());
    for (auto &data : que) {
        data.accepted = -1;
    }
    for (int i = 0; i < siz; i++) {
        que.push_back(ins[i]);
    }
    std::shuffle(ins.begin(), ins.end(), rng);
    std::shuffle(que.begin(), que.end(), rng);
    FILE *in = fopen(("sample" + file + ".in").c_str() , "w");
    FILE *ans = fopen(("sample" + file + ".ans").c_str(), "w");
    for (int i = 0; i < n; i++) {
        fprintf(in, "0 %s %d\n", ins[i].name.c_str(), ins[i].accepted);
    }
    for (int i = 0; i < m; i++) {
        fprintf(in, "1 %s\n", que[i].name.c_str());
    }
    for (int i = 0; i < m; i++) {
        fprintf(ans, "%d\n", que[i].accepted);
    }
    fprintf(in, "2\n");
    
    return 0;
}