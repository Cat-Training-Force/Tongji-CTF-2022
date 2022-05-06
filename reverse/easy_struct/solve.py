
rs=[2,0,4,1,4,3,4,0,1,1,3,4,0,1,2,1]
addr={
    0x563de437c229:'inc',0x563de437c244:'add',0x563de437c264:'sub',0x563de437c282:'xor',0x563de437c29d:'rol'
}
addrs=[0x563de437c264,0x563de437c229,0x563de437c244,0x563de437c229,0x563de437c244,0x563de437c29d,0x563de437c29d,0x563de437c282,0x563de437c29d,0x563de437c244,0x563de437c244,0x563de437c282,0x563de437c29d,0x563de437c229,0x563de437c264,0x563de437c244,]
rs=[addr[i] for i in addrs]
t=[0xf0,0x76,0x80,0x38,0xd9,0x69,0x36,0x2d,0x4e,0xac,0x8b,0x68,0x59,0x76,0x3,0xb5]
# void *fs[] = {inc, add, sub, xor,rol};
rrs={}
for i,r in enumerate(rs):
    if r not in rrs.keys():
        rrs[r]=[i]
    else:
        rrs[r].append(i)
print(rrs)
# {2: [0, 14], 0: [1, 7, 12], 4: [2, 4, 6, 11], 1: [3, 8, 9, 13, 15], 3: [5, 10]}
for i in rrs['inc']:
    t[i]-=1
# 1,3,13
t[0]+=t[1]
t[2]-=t[3]
# 0,2,12
t[15]-=t[0]
t[11]^=t[12]
# 11,15
t[10]-=t[11]
t[14]+=t[15]
# 10,14
t[9]-=t[10]
# 9
t[7]^=t[8]
t[4]-=t[5]

for i in range(len(t)):
    t[i]+=0x100
    t[i]&=0xff
    if t[i]<0x20 or t[i]>0x7e:
        print(i)
print(bytes(t))

