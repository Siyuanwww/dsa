# LAB3-1 Report

作者：丁思源 2022012901

---

## 哈希函数和冲突策略

1. 坏的哈希函数
   $$
   \operatorname{Hash}(s) = \lvert s \rvert\sum_{i = 0}^{n - 1} \operatorname{Asc}(s_i)
   $$
   其中 $\lvert s\rvert$ 表示 $s$ 的长度，$\operatorname{Asc}$ 是取 ASCII。
2. 好的哈希函数
   $$
   \operatorname{Hash}(s) = \sum_{i = 0} ^ {n - 1} \operatorname{Asc}(s_i) q^i \bmod{\text{table\_size}}
   $$
   其中 $q = 10007$。
3. 双向平方试探：在 QuadraticProbing 结构体内保存平方步长 $step$ 和目前的偏移方向 $sgn \in \{-1, 1\}$，每次试探时，偏移位置不断地左右跳跃，每隔一次则把 $step$ 加一（根据 $sgn$ 判断）。

```cpp
int QuadraticProbing::operator()(hash_entry* Table, int table_size, int last_choice) {
    int lst = sgn * step * step;
    sgn = -sgn;
    step += (sgn > 0);
    return ((last_choice - lst + sgn * step * step) % table_size + table_size) % table_size;
}
```

4. 公共溢出区：从哈希表中划分出 $400031$（$4k+3$ 型质数）的长度，剩余部分用作公共溢出区，在框架内使用 `dynamic_cast<PublicOverflow*>(my_collision)` 判断 `my_collision` 的派生类类型。如果在表中的哈希值位置无法插入，则在公共溢出区中按顺序从前往后尝试插入，查询亦然。

```cpp
static const int new_size = 400031;
int last_choice = (*my_hashing)(entry.my_string, new_size);
if (Table[last_choice].my_string == nullptr) {
    Table[last_choice] = entry;
    return true;
}
for (int i = new_size; i < table_size; i++) {
    if (Table[i].my_string == nullptr) {
        Table[i] = entry;
        return true;
    }
}
return false;
```

---

## 测试

按照查询和插入的字符串的分布方式，构造了三组数据。

设插入 $n$ 个数据，进行 $m$ 次查询，其中查询的字符串中，属于插入的字符串的共有 $\alpha m$ 个。

其中三组数据的 $n, m$ 均为 $10^5$，而 $\alpha$ 分别为 $1, 0.5, 0$。

数据构造采用 C++ 的 `std::mt19937` 作为随机数生成器，利用 `std::shuffle` 函数来打乱数据，核心代码如下：

```cpp
int n = 1e5, m = 1e5;
int siz = (int)m * alp;
std::shuffle(dataset.begin(), dataset.end(), rng);
std::vector<Info> ins(dataset.begin(), dataset.begin() + n);
std::vector<Info> que(dataset.end() - (m - siz), dataset.end());
for (int i = 0; i < siz; i++) {
    que.push_back(ins[i]);
}
std::shuffle(ins.begin(), ins.end(), rng);
std::shuffle(que.begin(), que.end(), rng);
```

测试结果如下（单位：秒）

| | “坏”的哈希函数 | “好”的哈希函数 |
| :--- | :--- | :--- |
| 线性探测 | 36.868 \| 48.908 \| 60.373 | 0.192 \| 0.199 \| 0.183 |
| 双向平方探测 | 0.639 \| 0.716 \| 0.812 | 0.195 \| 0.204 \| 0.179 |
| 公共溢出区 | 9.252 \| 13.553 \| 17.758 | 0.32 \| 0.563 \| 0.747 |

---

## 分析结果

1. “好”的哈希函数在所有冲突策略和所有数据下都相应地优于“坏”的哈希函数，原因是更均匀地将字符串映射到表中可以降低冲突的概率。
2. 线性探测性能劣于双向平方探测，因为其相邻位置的试探链的重合程度非常高，这也导致两者在非均匀映射下性能差异很大，而均匀映射下差异不太大。
3. 测试数据中，封闭散列更占优势。当数据的冲突很少时，公共溢出区则会体现出优势，并且空间连续性较好。
4. 理论上可以通过这个概率不均等设计哈希函数。大致的想法是将出现概率高的尽可能在散列表中映射地“远一点”，从而减少冲突的可能。
5. 动态扩容时可以将散列表的容量扩大两倍（但是如果为了满足双向平方探测的要求，可能需要在新的容量值附近取一个满足条件的质数），清空散列表再将所有的字符串重新插入。时间复杂度均摊每个字符串 $O(f(s))$，其中 $f(s)$ 是插入一个字符串所需要花费的时间，证明和 `vector` 扩容的时间复杂度证明相同。
