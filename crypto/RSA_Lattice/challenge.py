from Crypto.Util.number import *
from secret import flag
from os import urandom


def keyPairGeneration():
    i = 0
    while True:
        print(i)
        i += 1
        while True:
            d_p = getRandomNBitInteger(60)
            d_q = getRandomNBitInteger(60)
            k = getRandomNBitInteger(60)
            l = getRandomNBitInteger(60)
            if GCD(k ,l) == 1 and GCD(d_p, k) == 1 and GCD(d_q, l) == 1:
                break
        e = inverse(d_p, k) * inverse(l, k) * l + inverse(d_q, l) * inverse(k, l) * k
        c = getRandomNBitInteger(800)
        e += c * k * l
        assert e * d_q % l == 1
        assert e * d_p % k == 1
        p = (e * d_p - 1) // k + 1
        q = (e * d_q - 1) // l + 1
        if isPrime(p) and isPrime(q):
            return p*q, e


def rsa_enc(m, e, n):
    return pow(m, e, n)


n, e = keyPairGeneration()
m = bytes_to_long(flag)
c = rsa_enc(m, e, n)

print('n =', n)
print('e =', e)
print('c =', c)