import hashlib

a = '刘孔阳+Gitty RSA+Cat Training Force+247+21+广楼'
print(hashlib.md5(a.encode('utf-8')).hexdigest())
print(hashlib.md5('刘孔阳+NowYouSeeMe+Cat Training Force+247+21+广楼'.encode('utf-8')).hexdigest())
print('tjctf{%s}' % hashlib.sha256(a.encode('utf-8')).hexdigest())
keys = ["MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD",
        "SHOULD NOT", "RECOMMENDED",  "MAY", "OPTIONAL", 'NOT RECOMMENDED']
a = '/'.join(sorted(keys))+'+authorization handover+TS33501+5G RRC Layer'
print(a)
print(hashlib.md5(a.encode('utf-8')).hexdigest())
print('tjctf{%s}' % hashlib.sha256(a.encode('utf-8')).hexdigest())

a = [
    '/'.join(sorted(keys)),
    'authorization handover',
    'TS33501',
    '5G RRC Layer'
]
b = [
    'MAY/MUST/MUST NOT/NOT RECOMMANDED/OPTIONAL/RECOMMANDED/REQUIRED/SHALL/SHALL NOT/SHOULD/SHOULD NOT',
    'authorization handover',
    'TS33501',
    '5G RRC Layer',
]
a=a[0].split('/')
b=b[0].split('/')
for i in range(len(a)):
    if a[i] != b[i]:
        print(i, a[i], b[i])
b = [i.encode('utf-8') for i in b]
print(hashlib.md5(b'+'.join(b)).hexdigest())
