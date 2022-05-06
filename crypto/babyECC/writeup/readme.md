# babyECC
$Q = P * c_n$，求 $c_n$
可能会出现 sagecell 跑得很慢但是本地跑的很快的情况，但是基本没问题

## Challenge1
数据不大，直接求离散对数
```sage
c1 = P.discrete_log(Q)
```
c1 = 16102774641406563

## Challenge2: Pohlig-Hellman
对于 P，其阶可以分解为小*n+大，利用该性质求离散对数
```sage
factors, exponents = zip(*factor(E.order()))
primes = [factors[i] ^ exponents[i] for i in range(len(factors))][:-1]

dlogs = []
for fac in primes:
    t = int(int(P.order()) / int(fac))
    dlog = discrete_log(t*Q,t*P,operation="+")
    dlogs += [dlog]
    print("factor: "+str(fac)+", Discrete Log: "+str(dlog))

c2 = crt(dlogs,primes)
```
c2 = 13560702966457901


## Challenge3: Smart's Attack
异常情况下的 ECDLP：E、P 阶相等

```sage
def hensel_lift(curve, p, point):
    A, B = map(long, (E.a4(), E.a6()))
    x, y = map(long, point.xy())

    fr = y**2 - (x**3 + A*x + B)
    t = (- fr / p) % p
    t *= inverse_mod(2 * y, p)  # (y**2)' = 2 * y
    t %= p
    new_y = y + p * t
    return x, new_y

# lift points
x1, y1 = hensel_lift(E, p, g)
x2, y2 = hensel_lift(E, p, v)
mod = p ** 2

A2 = y2**2 - y1**2 - (x2**3 - x1**3)
A2 = A2 * inverse_mod(x2 - x1, mod)
A2 %= mod
B2 = y1**2 - x1**3 - A2 * x1
B2 %= mod

# new curve
E2 = EllipticCurve(IntegerModRing(p**2), [A2, B2])
# calculate dlog
g2s = (p - 1) * E2(x1, y1)
v2s = (p - 1) * E2(x2, y2)

x1s, y1s = map(long, g2s.xy())
x2s, y2s = map(long, v2s.xy())

dx1 = (x1s - x1) / p
dx2 = (y1s - y1) / p
dy1 = (x2s - x2)
dy2 = (y2s - y2)
c3 = dy1 * inverse_mod(int(dx1), int(p)) * dx2 * inverse_mod(int(dy2), int(p))
c3 %= p
```

另一种：
```sage
def SmartAttack(P,Q,p):
    E = P.curve()
    Eqp = EllipticCurve(Qp(p, 2), [ ZZ(t) + randint(0,p)*p for t in E.a_invariants() ])

    P_Qps = Eqp.lift_x(ZZ(P.xy()[0]), all=True)
    for P_Qp in P_Qps:
        if GF(p)(P_Qp.xy()[1]) == P.xy()[1]:
            break

    Q_Qps = Eqp.lift_x(ZZ(Q.xy()[0]), all=True)
    for Q_Qp in Q_Qps:
        if GF(p)(Q_Qp.xy()[1]) == Q.xy()[1]:
            break

    p_times_P = p*P_Qp
    p_times_Q = p*Q_Qp

    x_P,y_P = p_times_P.xy()
    x_Q,y_Q = p_times_Q.xy()

    phi_P = -(x_P/y_P)
    phi_Q = -(x_Q/y_Q)
    k = phi_Q/phi_P
    return ZZ(k)
```
c3 = 18405268938688863956870572894156796435757053022397239

合并即可
```python
from Crypto.Util.number import long_to_bytes

c1 = 16102774641406563
c2 = 13560702966457901
c3 = 18405268938688863956870572894156796435757053022397239

flag = long_to_bytes(c1) + long_to_bytes(c2) + long_to_bytes(c3)
print(flag)
# b'95cbf2c0-c38f-11ec-82a5-a45e60b7d5c7'
```
