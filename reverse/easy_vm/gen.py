
import numpy as np
import string
import random as rd
import struct
import z3

a=np.random.randint(0,2**16-1,(8,8))
print(np.linalg.matrix_rank(a))
flag=bytes([ord(rd.choice(string.hexdigits.lower())) for i in range(32)])
print('flag:',bytes(flag))
num=[]
for i in range(8):
    num.append(struct.unpack('<I',flag[i*4:i*4+4])[0])
print([hex(i) for i in num])
code=''
xor_data=np.random.randint(0,2**32-1,(8,1))
for i in range(8):
    xor_data[i]=(xor_data[i]+0x100000000)&0xffffffff
print(xor_data)
code=[]
target=[]
print(a)
for i in range(8):
    s=0
    code.append('push_num 0')
    for j in range(8):
        code.append('push_num %d'%abs(a[i][j]))
        code.append('push_data %d'%j)
        code.append('mul')
        if a[i][j]>=0:
            code.append('add')
        else:code.append('sub')
        s+=a[i][j]*num[j]
        if i==j:
            s^=xor_data[i]
            code.append('push_num %d'%xor_data[i])
            code.append('xor')
        s&=0xffffffff
    code.append('push_num %d'%s)
    code.append('test_eq')
    target.append(s)
code.append('exit')
print('target:',target)
print('code:',code)
def compile(code):
    res=b''
    op_dic={
        'push_num':b'\x07',
        'push_data':b'\x05',
        'double':b'\x06',
        'test_eq':b'\x08',
        'mul':b'\x04',
        'xor':b'\x03',
        'sub':b'\x02',
        'add':b'\x01',
        'exit':b'\x00'
    }
    for i in code:
        op=i.split(' ')[0]
        res+=op_dic[op]
        if op=='push_num' or op=='push_data':
            res+=struct.pack('<I',int(i.split(' ')[1]))
    return res
byte_code=compile(code)
print('byte_code:',len(byte_code),[i for i in byte_code])

def check(a,b,xor_data):
    print('===========================')
    print('a:',a)
    print('b:',b)
    print('xor:',xor_data)
    r=[z3.BitVec('r%d'%i,32) for i in range(8)]
    s=z3.Solver()
    for i in range(8):
        s.add(r[i]&0xff>=ord('0'))
        s.add(r[i]&0xff<=ord('z'))
        s.add((r[i]>>8)&0xff>=ord('0'))
        s.add((r[i]>>8)&0xff<=ord('z'))
        s.add((r[i]>>16)&0xff>=ord('0'))
        s.add((r[i]>>16)&0xff<=ord('z'))
        s.add((r[i]>>24)&0xff>=ord('0'))
        s.add((r[i]>>24)&0xff<=ord('z'))
    for i in range(8):
        cs=0
        for j in range(8):
            a_int=a[i][j].item()
            xor_d=xor_data[i].item()
            cs+=r[j]*a_int
            if i==j:
                cs^=xor_d
        b_d=b[i].item()
        s.add(cs==b_d)
    if s.check()==z3.sat:
        m=s.model()
        for i in range(8):
            if m[r[i]].as_long()!=num[i]:
                print('unsati:%d %x %x'%(i,num[i],m[r[i]].as_long()))
    else:
        print('unsati')

    for k in range(8):
        r=[z3.BitVec('r%d'%i,32) for i in range(8)]
        s=z3.Solver()
        for i in range(8):
            s.add(r[i]&0xff>=ord('0'))
            s.add(r[i]&0xff<=ord('z'))
            s.add((r[i]>>8)&0xff>=ord('0'))
            s.add((r[i]>>8)&0xff<=ord('z'))
            s.add((r[i]>>16)&0xff>=ord('0'))
            s.add((r[i]>>16)&0xff<=ord('z'))
            s.add((r[i]>>24)&0xff>=ord('0'))
            s.add((r[i]>>24)&0xff<=ord('z'))
        for i in range(8):
            cs=0
            for j in range(8):
                a_int=a[i][j].item()
                xor_d=xor_data[i].item()
                cs+=r[j]*a_int
                if i==j:
                    cs^=xor_d
            b_d=b[i].item()
            s.add(cs==b_d)
        s.add(r[k]!=num[k])
        if s.check()==z3.sat:
            print('multi-solve: %d %x'%(k,num[k]))
check(a,target,xor_data)
        