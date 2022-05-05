from base64 import *
from Crypto.Random import random
from secret import flag

alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/='


def keyGen():
    key = random.randint(1, 64)
    return key


def encode(m, key):
    c = b64encode(m.encode()).decode()
    res = ''
    for ch in c:
        idx = alphabet.find(ch)
        res += alphabet[(key * idx) % len(alphabet)]
    return res


key = keyGen()
c = encode(flag, key)
print('c =', c)
# c = BV2Jf1jnIVa+IVjE7=lnTjelov66
