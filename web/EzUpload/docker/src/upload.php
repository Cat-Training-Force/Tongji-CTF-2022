<div style="margin: 0 auto;margin-top: 100px; width: 500px;text-align: center;">
    <form action="" method="post" enctype="multipart/form-data">
        <label for="file">Filename:</label>
        <input type="file" name="file" id="file" />
        <input type="submit" name="submit" class="btn btn-primary" value="提交" /><br><br>
        只允许上传 jpg、png、gif、rar、zip 文件类型！
    </form>
    <br />
    <?php
    $type = array("jpg", "gif", "png", "rar", "zip");
    if (isset($_FILES['file'])) {
        $fileext = end(explode('.', $_FILES['file']['name']));
        if (!in_array($fileext, $type)) {
            echo "<script>alert('不允许上传这种类型的文件!')</script>";
            exit();
        } else {
            $uploadpath = 'upload/';
            $filename = md5(time()) . '.' . $fileext;
            $uploadfile = $uploadpath . $filename;
            move_uploaded_file($_FILES['file']['tmp_name'], $uploadfile);
            echo  '文件保存路径为: ' .  realpath(dirname(__FILE__)) . '/' . $uploadfile;
        }
    } else {
        exit();
    }

    ?>
</div>