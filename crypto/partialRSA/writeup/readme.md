# partialRSA

题目给出了 RSA n、e、c 以及 p xor q 的末400位

根据异或的性质，可以写一个 DFS 枚举所有可能的 p 低400位 的情况

然后对所有可能 p，尝试 RSA 已知 p 低位的攻击（Coppersmith Attack，网上常见的是已知 p 高位，需要略作修改）

由于数据设计的特点，运算均不会太久。

建议使用 SageMath

**C0pp3rsm17h_a77ack_0n_P_Low_b17s**