import random, time
from Crypto.Cipher import AES
from Crypto import Random
from Crypto.Util.number import bytes_to_long, long_to_bytes
from secret import flag


class CyberCat:
	def Meow(self, length=32):
		return random.getrandbits(length)

	def __init__(self):
		random.seed(time.time())


def getRecord(cat):
	f = open('./MeowRecord', mode='w')
	for i in range(624):
		word = cat.Meow()
		wordStr = str(hex(word))[2:]
		wordStr = wordStr.zfill(8)
		# print(wordStr)
		f.write(wordStr)
	f.close()


def encrypt(key, flag):
	iv = Random.new().read(AES.block_size)
	aesObj = AES.new(key, AES.MODE_CFB, iv)
	cipherText = iv + aesObj.encrypt(flag.encode())
	return bytes_to_long(cipherText)


def decrypt(key, cipherText):
	aesObj = AES.new(key, AES.MODE_CFB, cipherText[0:16])
	print(aesObj.decrypt(cipherText[16:]).decode())


def hint():
	# Cat Training
	tjCat = CyberCat()
	# getRecord(tjCat)
	flag = "tjctf{Hello_TJCTF}"
	key = tjCat.Meow(128)
	print('Key:', key)
	# Encode
	key = long_to_bytes(key)
	cipher = encrypt(key, flag)
	print('Cipher:', cipher)
	# Decode
	cipher = long_to_bytes(cipher)
	decrypt(key, cipher)


# Here Comes Challenge
tjCat = CyberCat()
getRecord(tjCat)
key = tjCat.Meow(128)
# print('key=', key)

cipher = encrypt(long_to_bytes(key), flag)
print('cipher=', cipher)

# cipher = 9152309718736889107934805995355481848586655727279784510831079348301489271659038763451948983819657562


