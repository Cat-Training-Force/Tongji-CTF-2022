import hashlib
quest=[
    '1. RFC中用于指代要求水平的关键词有哪几个(/分隔,字母序)',
    '2. RFC中,IoT设备到达生命周期之后,为了让用户可以继续使用或升级设备,需要做什么(两个英语单词)',
    '3. 根据某RFC,5G的安全需求在哪儿记录了(一个文件代号)',
    '4. 5G协议中,包含安全的层是哪一层(答案格式: 5G X Layer, X是层名)'
]

s = []
for q in quest:
    print(q)
    a=input('Please Input the answer: ').strip()
    s.append(a.encode('utf-8'))
if hashlib.md5(b'+'.join(s)).hexdigest()=='0c16bd770d2265bccaf2da6922f2b90a':
    print('please submit tjctf{%s}'%hashlib.sha256(b'+'.join(s)).hexdigest())
else:
    print('something wrong')