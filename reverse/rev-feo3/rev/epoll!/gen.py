import random
flag = "tjctj{3PolL_1$_N07_4_600D_1DEA}\0"
v = [int.from_bytes(flag[i:i+4].encode(), 'little') for i in range(0, len(flag), 4)]
print(v)
a0 = v[0];
a1 = v[1];
a2 = v[2];
a3 = v[3];
a4 = v[4];
a5 = v[5];
a6 = v[6];
a7 = v[7];
print('res:')
print([
    a0 + a1 + a2 + a3 - a4 - a5 - a6 - a7,
    a0 + a1 + a2 - a3 - a4 - a5 - a6 + a7,
    a0 + a1 - a2 - a3 - a4 - a5 + a6 + a7,
    a0 - a1 - a2 - a3 - a4 + a5 + a6 + a7,
    -a0 - a1 - a2 - a3 + a4 + a5 + a6 + a7,
    -a0 - a1 - a2 + a3 + a4 + a5 + a6 - a7,
    -a0 - a1 + a2 + a3 + a4 + a5 - a6 - a7,
    -a0 + a1 + a2 + a3 + a4 - a5 - a6 - a7])

t = [0, 0, 0, 0, 1, 1, 1, 1] * 2
res = []
for i in range(8):
    v = 0
    l = list(zip(t[i:i+8], range(8)))
    random.shuffle(l)
    if l[0][0] == 0 and l[0][1] == 0:
        l = l[::-1]
    for a, b in l:
        v = (v << 4) | (a << 3) | b
    res.append(v)
print('insts:')
print(res)
