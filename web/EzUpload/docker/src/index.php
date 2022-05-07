<html>

<head>
    <title>
        EzUpload
    </title>
    <style>
        .ul {
            margin: 0 auto;
        }

        body ul {
            list-style: none;
        }

        a:visited {
            color: #0000BB;
        }

        ul li a {
            text-decoration: none;
            margin-right: 10px;
            text-align: center;
            width: 150px;
            list-style: none;
            padding: 10px;
            border: 1px dashed #EEE;
            float: left;
        }

        ul li a:hover {
            background: #EEE;
        }

        #index {
            text-align: center;
            margin: 0 auto;
            width: 500px;
        }
    </style>
</head>

<body>
    <div id="index" class="ul">
        <h2>EzUpload</h2>
        <ul>
            <li>
                <a href="index.php">首页</a>
            </li>
            <li>
                <a href="index.php?url=upload">上传文件</a>
            </li>
        </ul>
    </div>
    <br />
    <br />
<?php
error_reporting(0);
// header('Content-Type:text/html;charset=utf-8');
$url = "";
if (empty($_REQUEST["url"]) || $_REQUEST["url"] === "index") {
    echo '<h3 style="text-align: center;">快让我看看你藏了什么好东西！</h2>';
    exit;
} else {
    $url = preg_replace('/%+/', "", $_REQUEST["url"]);
    require($url . ".php");
}
?>
</body>

</html>
