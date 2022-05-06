from pwn import *
from functools import partial
from timeit import timeit

# context.log_level = 'debug'

code = {
	'A': '.-',     'B': '-...',   'C': '-.-.',   'D': '-..',   'E': '.',
	'F': '..-.',   'G': '--.',    'H': '....',   'I': '..',    'J': '.---',
	'K': '-.-',    'L': '.-..',   'M': '--',     'N': '-.',    'O': '---',
	'P': '.--.',   'Q': '--.-',   'R': '.-.',    'S': '...',   'T': '-',
	'U': '..-',    'V': '...-',   'W': '.--',    'X': '-..-',  'Y': '-.--',
	'Z': '--..',   '0': '-----',  '1': '.----',  '2': '..---', '3': '...--',
	'4': '....-',  '5': '.....',  '6': '-....',  '7': '--...', '8': '---..',
	'9': '----.',  ',': '--..--', '.': '.-.-.-', ' ': ' ',     '_': '..--.-',
	'?': '..--..', ';': '-.-.-.', ':': '---...', "'": '.----.',
	'-': '-....-', '/': '-..-.',  '(': '-.--.', ')': '-.--.-'
}
rcode = {y: x for x, y in code.items()}

def morse_decode(text: str) -> str:
	return ''.join([rcode[k] for k in text.split(' ')])

conn = remote('127.0.0.1', 30110)
conn.recvuntil('Are you ready to read the book?\n')
conn.sendline('')

text = ''
func = partial(conn.recv, 1, timeout=5)
while True:
	try:
		time = timeit(func, number=1)
	except EOFError:
		break
	else:
		if time < 0.4:
			text += '.'
		elif time < 0.7:
			text += '-'
		else:
			text += ' '

conn.close()

print(text)
text_decode = morse_decode(text)

print(text_decode)
