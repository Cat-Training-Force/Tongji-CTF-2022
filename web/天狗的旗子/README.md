## 天狗的旗子

`tjctf{fORW@Rd_Y0ur_f1a6}`

送分题

访问 `/flag` 返回的是假的 flag。

访问 `/robots.txt` 找到隐藏路径。

```
User-agent: *

Disallow: /feasgsdrgvsefzergvsdfvsvgswgewrf
```

访问 `/feasgsdrgvsefzergvsdfvsvgswgewrf`，提示需要 localhost 才能访问。

在请求头中添加

```
X-Forwarded-For: localhost
```

即可拿到flag。