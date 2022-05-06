# RSA_Lattice

题目给出了一种奇怪的生成方式：

1. 60位的 dp、dq、k、l，彼此互质
2. 800位的 填充数 c
3. 利用 dp、dq、k、l 生成的 e

并且给出了如下性质

1. ![](https://latex.codecogs.com/gif.image?\\dpi{110}e&space;*&space;d_q&space;\bmod&space;l&space;=1&space;)

2. ![](https://latex.codecogs.com/gif.image?\\dpi{110}e&space;*&space;d_p&space;\bmod&space;k&space;=1)

然后利用 e、dp、dq 生成了 RSA 子素数 p、q

数据上看，n 接近2000 bits，暴力分解几乎无望，那么只能从性质入手：

根据题目名的提示，需要使用到格进行攻击，实际上这个性质符合一篇知名[Paper](https://www.iacr.org/archive/crypto2007/46220388/46220388.pdf)

其中介绍了 Bleichenbacher-May Attack 所用的格基规约，把公式展开可以写成格的形式：
![](https://latex.codecogs.com/gif.image?%5Cdpi%7B110%7D%5Cbegin%7Bbmatrix%7Dd_pd_q%20&%20d_p(l-1)&plus;d_q(k-1)%20&%20kl%5Cend%7Bbmatrix%7D%5Cbegin%7Bbmatrix%7De%5E2%20%20%20%20&%201&0&0%5C%5Ce%20%20%20%20%20%20&%200&1&0%5C%5C-(N-1)%20&%200&0&1%5C%5C%5Cend%7Bbmatrix%7D=%5Cbegin%7Bbmatrix%7Dk&plus;l-1%20&%20d_pd_q%20&%20d_p(l-1)&plus;d_q(k-1)%20&%20kl%5Cend%7Bbmatrix%7D)

乘一个平衡用的对角矩阵 [2^60,1,1,1]，即可得到 k+l-1，kl

然后利用 z3-solver 暴力求解即可得到 k、l，当然其他求解手段也可以

有了 k、l，就可以结合 e 去恢复出 dp、p，做基础的 RSA 求解

**He1l0_B13ich3nb4cher-M4y_A77ack**
