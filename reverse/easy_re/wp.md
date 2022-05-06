
flag: flag{$tArt_R3v3rs1nG_by_XOR!}

签到题，简单XOR

使用IDA F5，得到加密函数

```cpp
for ( i = 0LL; ; ++i )
  {
    result = i;
    if ( i >= a2 )
      break;
    *(_BYTE *)(a1 + i) ^= byte_4010[i];
  }
  return result;
```

即简单xor

获取key和秘文，就可以得到明文

```python
a=[15, 91, 153, 255, 186, 185, 174, 24, 241, 125, 34, 156, 33, 100, 171, 16, 131, 230, 93, 170, 87, 194, 51, 156, 39, 5, 79, 253, 117]
b=[105, 55, 248, 152, 193, 157, 218, 89, 131, 9, 125, 206, 18, 18, 152, 98, 240, 215, 51, 237, 8, 160, 74, 195, 127, 74, 29, 220, 8]
print(bytes([a[i]^b[i] for i in range(len(a))]))
# flag{$tArt_R3v3rs1nG_by_XOR!}
```
