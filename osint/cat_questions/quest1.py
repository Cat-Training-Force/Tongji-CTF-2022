import hashlib
quest = [
    '1. 2021年CTF谁是特等奖',
    '2. 2021年CTF哪道题没有人做出来',
    '3. 同济大学CTF战队名称是什么(三个空格分隔的单词,首字母大写)',
    '4. 2021年同济大学CTF中Reverse方向赛题Endless源代码有多少行(纯数字)',
    '5. 2017年TongjiCTF共有多少道题(纯数字)',
    '6. 同济大学嘉定校区华楼和迩楼之间的是什么楼(楼的中文名)'
]
s = []
for q in quest:
    print(q)
    a=input('Please Input the answer: ').strip()
    s.append(a.encode('utf-8'))
if hashlib.md5(b'+'.join(s)).hexdigest()=='7a139e66bc946bfb845f3edd8f095e4b':
    print('please submit tjctf{%s}'%hashlib.sha256(b'+'.join(s)).hexdigest())
else:
    print('something wrong')