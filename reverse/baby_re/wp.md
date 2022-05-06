
首先IDA分析一波

```cpp
sub_155D(a1, a2, a3);
  puts("Input: ");
  memset(s, 0, sizeof(s));
  read(0, s, 0xFFuLL);
  v3 = strlen(s);
  v5 = v3 - 1;
  s[v3] = 0;
  strcpy(dest, s);
  v6 = (void (__fastcall *)(char *, size_t))sub_15A0();
  v6(s, v5);
  if ( (unsigned int)sub_167D(s, v5) )
    fprintf(stdout, "Your flag is: %s\n", dest);
  else
    fwrite("Try Again!!!\n", 1uLL, 0xDuLL, stdout);
  fflush(stdout);
```

输入之后，调用了sub_15A0返回的函数进行加密，然后验证

gdb起一下，看看这个加密函数是啥

```sh
pwndbg> file ./baby_re 
Reading symbols from ./baby_re...
(No debugging symbols found in ./baby_re)
pwndbg> r
Starting program: baby_re 
[Inferior 1 (process 160447) exited with code 0377]
```

直接退出，可是直接运行没有问题

主函数没有发现反调试，那么就可能在init里面

确实有个函数，有花指令，但是不影响观看

```asm
.text:000000000000181A ; __unwind {
.text:000000000000181A                 endbr64
.text:000000000000181E                 push    rbp
.text:000000000000181F                 mov     rbp, rsp
.text:0000000000001822                 sub     rsp, 30h
.text:0000000000001826                 mov     rax, fs:28h
.text:000000000000182F                 mov     [rbp-8], rax
.text:0000000000001833                 xor     eax, eax
.text:0000000000001835                 jz      short loc_183A
.text:0000000000001837                 jnz     short loc_183A
.text:0000000000001837 ; ---------------------------------------------------------------------------
.text:0000000000001839                 db 0FFh
.text:000000000000183A ; ---------------------------------------------------------------------------
.text:000000000000183A
.text:000000000000183A loc_183A:                               ; CODE XREF: .text:0000000000001835↑j
.text:000000000000183A                                         ; .text:0000000000001837↑j
.text:000000000000183A                 mov     edi, 0
.text:000000000000183F                 mov     eax, 0
.text:0000000000001844                 call    _ptrace
.text:0000000000001849                 cmp     rax, 0FFFFFFFFFFFFFFFFh
.text:000000000000184D                 jnz     short loc_1859
.text:000000000000184F                 mov     edi, 0FFFFFFFFh
.text:0000000000001854                 call    _exit
.text:0000000000001859 ; ---------------------------------------------------------------------------
.text:0000000000001859
.text:0000000000001859 loc_1859:                               ; CODE XREF: .text:000000000000184D↑j
.text:0000000000001859                 mov     rax, 801CC794FCA46533h
.text:0000000000001863                 mov     rdx, 0F32356C259CF4BDCh
.text:000000000000186D                 mov     [rbp-30h], rax
.text:0000000000001871                 mov     [rbp-28h], rdx
.text:0000000000001875                 mov     rax, 0DDC068D86788EFABh
.text:000000000000187F                 mov     rdx, 8FDD7D628AC9D361h
.text:0000000000001889                 mov     [rbp-20h], rax
.text:000000000000188D                 mov     [rbp-18h], rdx
.text:0000000000001891                 mov     rax, 5D89F18751348A61h
.text:000000000000189B                 mov     [rbp-10h], rax
.text:000000000000189F                 mov     rax, [rbp-30h]
.text:00000000000018A3                 mov     rdx, [rbp-28h]
.text:00000000000018A7                 mov     cs:qword_4160, rax
.text:00000000000018AE                 mov     cs:qword_4168, rdx
.text:00000000000018B5                 mov     rax, [rbp-20h]
.text:00000000000018B9                 mov     rdx, [rbp-18h]
.text:00000000000018BD                 mov     cs:qword_4170, rax
.text:00000000000018C4                 mov     cs:qword_4178, rdx
.text:00000000000018CB                 mov     rax, [rbp-10h]
.text:00000000000018CF                 mov     cs:qword_4180, rax
.text:00000000000018D6                 nop
.text:00000000000018D7                 mov     rax, [rbp-8]
.text:00000000000018DB                 xor     rax, fs:28h
.text:00000000000018E4                 jz      short locret_18EB
.text:00000000000018E6                 call    ___stack_chk_fail
.text:00000000000018EB ; ---------------------------------------------------------------------------
.text:00000000000018EB
.text:00000000000018EB locret_18EB:                            ; CODE XREF: .text:00000000000018E4↑j
.text:00000000000018EB                 leave
.text:00000000000018EC                 retn
.text:00000000000018EC ; } // starts at 181A
```

那么反调试就在ptrace那里了。并且这个函数里替换了一些数据

patch掉反调试，回头看

这次可以成功起了，但是随便输入发现会退出，而且就在调用解密代码的地方

```
pwndbg> r
Starting program: /home/tom/Downloads/baby_re1 
Input: 
flag{123456}

Program received signal SIGSEGV, Segmentation fault.
0x00007ffff7ffb00c in ?? ()
LEGEND: STACK | HEAP | CODE | DATA | RWX | RODATA
```

分析一下解密函数

```cpp
v3 = mmap(0LL, 0x250uLL, 7, 34, -1, 0LL);
  if ( !v3 )
  {
    v0 = __errno_location();
    fprintf(stderr, "MMAP failed: %d\n", (unsigned int)*v0);
    exit(1);
  }
  for ( i = 0LL; i < 0x128; ++i )
    v3[i] = byte_4290[i & 0xF] ^ byte_4020[i];
  return v3;
```

就是个xor

byte_4290是计算代码校验生成的，4020是静态数据

这里可以查看一下校验码(4290)的生成方法

```cpp
void *__fastcall sub_1309(int *a1, _QWORD *a2, size_t a3)
{
  void *result; // rax
  int v4; // edx
  bool v6; // [rsp+23h] [rbp-Dh]
  int v7; // [rsp+24h] [rbp-Ch]
  unsigned __int64 i; // [rsp+28h] [rbp-8h]

  memset(a1, 0, 0x10uLL);
  if ( a3 <= 0xF )
    return memcpy(a1, a2, a3);
  v6 = 0;
  *a1 = *(_QWORD *)((char *)a2 + 4);
  a1[1] = a2[1];
  a1[2] = *(_QWORD *)((char *)a2 + 12);
  a1[3] = *a2;
  if ( (a3 & 0xF) != 0 )
    a3 -= 16LL;
  for ( i = 16LL; ; i += 16LL )
  {
    result = (void *)i;
    if ( i >= a3 )
      break;
    if ( v6 )
    {
      *a1 ^= LODWORD(a2[i / 8]);
      a1[1] ^= HIDWORD(a2[i / 8]);
      a1[2] ^= LODWORD(a2[i / 8 + 1]);
      v4 = a1[3] ^ HIDWORD(a2[i / 8 + 1]);
    }
    else
    {
      *a1 += LODWORD(a2[i / 8]);
      a1[1] += HIDWORD(a2[i / 8]);
      a1[2] += LODWORD(a2[i / 8 + 1]);
      v4 = a1[3] + HIDWORD(a2[i / 8 + 1]);
    }
    a1[3] = v4;
    v7 = *a1;
    *a1 = a1[1];
    a1[1] = a1[2];
    a1[2] = a1[3];
    a1[3] = v7;
    v6 = !v6;
  }
  return result;
}
```

即两个函数之间的所有代码做一个hash，这样才可以正确解密代码。这里无法用gdb软件断点调试获取这个计算结果，详细可以了解一下几种断点以及[底层原理](https://blog.csdn.net/gengzhikui1992/article/details/111856016#:~:text=%E6%96%AD%E7%82%B9%E5%92%8C%E5%8D%95%E6%AD%A5,%E3%80%81I%2FO%E6%96%AD%E7%82%B9%E3%80%82)

这里就直接使用IDA脚本解密代码了

```python
import ida_bytes as ib
import struct
state=[0,0,0,0]
data=get_bytes(0x1309,0x18ed-0x1309)
e=False
l=len(data) if len(data)%16==0 else len(data)-16
def u32(b):
    return struct.unpack("<I",b)[0]
def p32(b):
    # print(b)
    return struct.pack("<I",b)
d=data
state=[u32(d[4:8]),u32(d[8:12]),u32(d[12:16]),u32(d[:4])]
for i in range(16,l,16):
    if e:
        state[0]^=u32(data[i:i+4])
        state[1]^=u32(data[i+4:i+8])
        state[2]^=u32(data[i+8:i+12])
        state[3]^=u32(data[i+12:i+16])
    else:
        state[0]+=u32(data[i:i+4])
        state[1]+=u32(data[i+4:i+8])
        state[2]+=u32(data[i+8:i+12])
        state[3]+=u32(data[i+12:i+16])
        state[0]&=0xffffffff
        state[1]&=0xffffffff
        state[2]&=0xffffffff
        state[3]&=0xffffffff
    t=state[0]
    state[0]=state[1]
    state[1]=state[2]
    state[2]=state[3]
    state[3]=t
    e=not e
k=p32(state[0])+p32(state[1])+p32(state[2])+p32(state[3])
print('key:',[hex(i) for i in k])
d=get_bytes(0x4020,len(data))
d=[d[i]^k[i%16] for i in range(len(data))]
for i in range(len(data)):
    ib.patch_bytes(0x4020,bytes(d))
```

这回再查看4020,就可以正常反汇编了，这里发现IDA无法反编译，就用ghidra试一下

```cpp
void UndefinedFunction_00104020(long param_1,ulong param_2)

{
  //...
  
  uStack72 = param_2;
  if ((param_2 & 7) != 0) {
    uStack72 = param_2 - 8;
  }
  for (uStack16 = 0; uStack16 < uStack72; uStack16 = uStack16 + 8) {
    uStack20 = *(uint *)(uStack16 + param_1);
    uStack24 = *(uint *)(param_1 + uStack16 + 4);
    iStack28 = 0;
    for (uStack32 = 0; uStack32 < 0x20; uStack32 = uStack32 + 1) {
      iStack28 = iStack28 + -0x61c88647;
      uStack20 = uStack20 +
                 ((uStack24 >> 5) + 0x2d73692d ^ uStack24 * 0x10 + 0x73696854 ^ iStack28 + uStack24)
      ;
      uStack24 = uStack24 +
                 ((uStack20 >> 5) + 0x79656b2d ^ uStack20 * 0x10 + 0x74736562 ^ iStack28 + uStack20)
      ;
    }
    *(uint *)(param_1 + uStack16) = uStack20;
    *(uint *)(uStack16 + 4 + param_1) = uStack24;
  }
  return;
}
```

可以看到就是tea算法，关于tea解法查询[ctfwiki](https://ctf-wiki.org/reverse/identify-encode-encryption/introduction/)即可

tjctf{34Bf9acCdD8e412871Ae3ceCE-8A0Ca33}