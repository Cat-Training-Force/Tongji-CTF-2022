<?php
error_reporting(0);
highlight_file(__FILE__);

$flag = file_get_contents("/flag");
$a = $_GET['a'];
$b = unserialize($a);
$b->c = $flag;
foreach ($b as $key => $value) {
    if ($key === 'c') {
        continue;
    }
    echo $value;
}
