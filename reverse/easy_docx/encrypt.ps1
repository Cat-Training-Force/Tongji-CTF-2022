function init($key){
    $s=0..255
    $k=0..255
    foreach($i in 0..255){
        $k[$i]=[int]$key[$i%$key.Length]
    }
    $j=0
    foreach($i in 0..255){
        $j=($j+$s[$i]+$k[$i])%256
        $s[$i],$s[$j]=$s[$j],$s[$i]
    }
    return $s
}
function encrypt([byte[]]$s,$d){
    $i,$j,$t=0,0,0
    foreach($k in 0..($d.Length-1)){
        $i=($i+1)%256
        $j=($j+$s[$i])%256
        $s[$i],$s[$j]=$s[$j],$s[$i]
        $t=($s[$i]+$s[$j]+1)%256
        $d[$k]=$d[$k] -bxor $s[$t]
    }
    return $d
}
$s=init 'N0thing_to_see'
$f=[System.IO.File]::ReadAllBytes("update2.dll")
$d=encrypt $s $f
[System.IO.File]::WriteAllBytes('update_enc.dll',$d)

# powershell -executionpolicy bypass -file .\encrypt.ps1