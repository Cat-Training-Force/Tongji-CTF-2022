from Crypto.Cipher import AES
from randcrack import RandCrack
from Crypto.Util.number import long_to_bytes


def decrypt(key, cipherText):
    aesObj = AES.new(key, AES.MODE_CFB, cipherText[0:16])
    print(aesObj.decrypt(cipherText[16:]).decode())


rc = RandCrack()

with open('MeowRecord') as f:
    record = f.read()
    f.close()
    for i in range(int(len(record)/8)):
        value = record[i*8:i*8+8]
        rc.submit(int(value, 16))

key = rc.predict_getrandbits(128)
key = long_to_bytes(key)
cipher= 9152309718736889107934805995355481848586655727279784510831079348301489271659038763451948983819657562
cipher = long_to_bytes(cipher)
decrypt(key, cipher)
# 'tjctf{mt_r4nd0m_1s_un5afe}'