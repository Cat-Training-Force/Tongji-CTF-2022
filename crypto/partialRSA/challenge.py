from Crypto.Util.number import getPrime
from secret import flag

p = getPrime(512)
q = getPrime(512)
n = p*q
lowXorBit = (p ^ q) % pow(2, 400)

print('n =', n)
print('x =', lowXorBit)
