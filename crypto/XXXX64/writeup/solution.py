from base64 import *
from Crypto.Random import random

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
    print('b64:', c)
    return res


def decode(c):
    idx = alphabet.find('=')
    # Get Key
    key = 0
    while key < 65:
        if alphabet[(key * idx) % len(alphabet)] == c[-1]:
            print(key)
            break
        key += 1
    # Calculate Table
    dTable = ''
    for ch in alphabet:
        idx = alphabet.find(ch)
        dTable += alphabet[(key * idx) % len(alphabet)]
    res = ''
    # Find in Dtable
    for ch in c:
        idx = dTable.find(ch)
        res += alphabet[idx]
    return res


c = "BV2Jf1jnIVa+IVjE7=lnTjelov66"
m = decode(c)
print(b64decode(m.encode()).decode())
