# LAB3-1 Report

作者：丁思源 2022012901

---

## 哈希函数和冲突策略

1. 坏的哈希函数
   $$
   \operatorname{Hash}(s) = \bigoplus_{i = 0}^{n - 1} \operatorname{Asc}(s_i)
   $$
   其中 $\bigoplus$ 是异或函数，$\operatorname{Asc}$ 是取 ASCII。
2. 好的哈希函数
   $$
   \operatorname{Hash}(s) = \sum_{i = 0} ^ {n - 1} \operatorname{Asc}(s_i) q^i \bmod{\text{table\_size}}
   $$
   其中 $q = 10007$。
3. 双向平方试探：在 QuadraticProbing 结构体内保存平方步长 $step$ 和目前的偏移位置 $offset$，每次试探时，偏移位置不断地左右跳跃，每隔一次则把 $step$ 加一。
4. 公共溢出区：从哈希表中划分出 $400031$ 的长度，剩余部分用作公共溢出区，在框架内使用 `dynamic_cast` 判断 `my_collision` 的派生类类型。如果在表中的哈希值位置无法插入，则在公共溢出区中按顺序从前往后尝试插入，查询亦然。

---

## 测试



---

## 分析结果

