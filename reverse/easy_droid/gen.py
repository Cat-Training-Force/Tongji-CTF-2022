
t=[i for i in '3gJ73Sj+tt3YognBuQN6sSi74T3lz8vQtwJPtSv6']
print(len('tjctf{K0t1in_AnDr0id_s3cUriTy}'))
for i in range(0,len(t)-1,2):
    t1=t[i]
    t[i]=t[i+1]
    t[i+1]=t1
for i in range(0,len(t)//2):
    t1=t[i]
    t[i]=t[len(t)-i-1]
    t[len(t)-i-1]=t1
print(''.join(t))
print(' '.join(hex(i)[2:].rjust(2,'0') for i in range(30)))