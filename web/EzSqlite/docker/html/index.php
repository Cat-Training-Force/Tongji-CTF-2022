<html>
<head>
    <title>EzSqlite</title>
</head>
<body>
<h3>Easy Sqlite</h3>
<h3>Just inject me!</h3>
<hr>
<form method='POST'>
    give me id or username<br>
    <input type=text name='id' placeholder='id'><br>
    <input type=text name='username'placeholder='username'><br>
    <input type=submit value='提交'>
</form>
</body>
</html>
<?php
error_reporting(0);
class MyDB extends SQLite3
{
    function __construct()
    {
        $this->open('/tjctf.db');
    }
}
function check($s){
    if(preg_match("/'|#|-|sleep|union/i",$s))
    {
        die('hack!');
    }
}
$db = new MyDB();
$id = $_POST['id'];
$username = $_POST['username'];
check($id);
check($username);
$sql ="SELECT username from ctf where id=$id or username='$username'";
$ret = $db->query($sql);
while($row = $ret->fetchArray(SQLITE3_ASSOC) ){
    echo $row['username'];
}
$db->close();
?>
