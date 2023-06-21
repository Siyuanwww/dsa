# PA4-2-2 Whistory Report

定义两个字符串相同，当且仅当存在一个循环位移相同。对每个字符串，求出编号最小的相同字符串。

使用字符串哈希，简单地采用 $\sum_{k = 0}^{n - 1} s_k \cdot Base^{k}$，并利用 $64$ 位无符号整数的自然溢出。

对于每个字符串，求出 $m$ 个未经过循环位移的哈希值；之后对每个字符串，$\mathcal O(n)$ 求出 $n$ 个循坏位移的哈希值，利用二分查找来判断 $m$ 个哈希值中是否存在相同的值。

吐槽：这题卡我 $10^9+7$ 的单模哈希！又卡我双哈希！

时间复杂度：$\mathcal O(nm \log m)$

空间复杂度：$\mathcal O(nm)$

---

困难和参考资料：无

用时：1h