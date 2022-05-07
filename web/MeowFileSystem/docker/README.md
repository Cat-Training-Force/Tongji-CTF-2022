# EasyFS

## 简介
&emsp;轻量级文件服务器，支持缩略图，支持单选、多选，下载支持中文名，不依赖其它容器，可独立部署，使用Java语言、SpringBoot框架开发。

<br>

> 在线演示：[在线演示](http://139.199.158.165:8081/)，演示系统关闭上传和删除功能。

## 独立部署
1. 下载打包好的可部署文件 [最新版下载](https://gitee.com/whvse/easy-fs/releases)；
2. 执行start.bat文件，linux使用命令nohup java -jar xxx.jar；
3. 访问 `http://localhost:8081/`，即可在线管理文件。 

> &emsp;你也可以使用IDEA导入源码运行，如果是SpringMVC项目可复制源码FileController到你的项目里面使用。

<br>

## 项目截图

在线管理：

![在线管理](https://ws1.sinaimg.cn/large/88052d6bly1fyk664e4laj20ou0fsgn6.jpg)

选择文件：

![用户管理](https://ws1.sinaimg.cn/large/88052d6bly1fyk66zs1tsj20ou0fsjtr.jpg)

<br>

## 使用指南

### 上传接口
`http://文件服务器ip:8081/file/upload`，使用POST方式，传递file参数：

```html
<button id="btnUpload">上传文件</button>

<script>
layui.use(['jquery', 'layer', 'upload'], function () {
        var $ = layui.jquery;
        var layer = layui.layer;
        var upload = layui.upload;

        // 上传文件事件
        upload.render({
            elem: '#btnUpload',
            url: 'file/upload',
            choose: function (obj) {
                layer.load(2);
            },
            done: function (res, index, upload) {
                layer.closeAll('loading');
                if (res.code == 200) {
                    layer.msg('上传成功', {icon: 1});
                    // res.url;   文件地址
                    // res.smUrl;  缩略图地址
                } else {
                    layer.msg('上传失败', {icon: 2});
                }
            },
            error: function () {
                layer.closeAll('loading');
                layer.msg('上传失败', {icon: 2});
            },
            accept: 'file'
        });

    });
</script>
```
&emsp;返回数据：`{"code": 200, "msg": "上传成功", "url": "2018/12/24/xxx.png", "smUrl": "sm/2018/12/24/xxx.png"}`。

<br>

### 查看/下载接口
```html
<a href="file/2018/12/24/xxx.png">查看源文件</a>
<a href="file/sm/2018/12/24/xxx.png">查看缩略图</a>
```
&emsp;如果是图片、音频、视频、pfd、网页、文本类型的文件会在浏览器直接打开，其他类型弹出下载框。

<br>

### 打开选择文件弹窗
```javascript
layer.open({
    type: 2,
    title: '选择文件',
    content: 'fileChoose.html?multi=true',
    area: ['600px', '420px'],
    offset: '50px',
    shade: .1,
    fixed: false,
    resize: false,
    end: function () {
        if (typeof(mFsUrls) != "undefined" && mFsUrls.length > 0) {
            layer.msg('你选择了：' + JSON.stringify(mFsUrls), {icon: 1});
            mFsUrls = undefined;
        }
    }
});
```
&emsp;上面是使用layer弹窗插件打开选择文件弹窗，`fileChoose.html`是弹窗页面，如果是独立部署，写`http://文件服务器ip:8081/fileChoose.html`。

**参数配置：**

 参数名 | 描述 | 可选值
 --- | --- | ---
 accept | 允许上传的文件类型 | image(图片)、video(视频)、audio(音频)、file(所有文件)
 exts | 允许上传的后缀 | 使用`,`分割，例如`jpg,png`,就不能上传gif
 multi | 是否是多选 | true和false，不写默认为false
 maxNum| 多选时最多选择几个 | 默认无限
 
 > 示例： fileChoose.html?accept=image&exts=png,jpg&multi=false

<br>

### 服务器参数配置
&emsp;默认配置为上传到第一个硬盘的`EasyFS/`文件夹中，并且会生成图片缩略图。

**可选参数：**

 参数名称 | 描述 | 可选值
 --- | --- | ---
 fs.dir | 文件上传位置 | 默认是`EasyFS/`
 fs.uuidName | 是否使用uuid命名 | 默认为`false`,使用文件原本名字，存在则加`(1)`
 fs.useSm | 是否生成缩略图 | 默认为`true`
 fs.useNginx | 是否使用nginx作为服务器 | 默认为`false`
 fs.nginxUrl | nginx服务器地址 | 


&emsp;修改application.properties文件重新打包部署即可，如果不想重新打包，可通过如下方式修改：

```text
// 修改start.bat
java -jar easy-fs-1.0.jar --fs.dir=XXX/ --fs.uuidName=true
```

&emsp;使用nginx作为服务器，`fs.dir`写nginx的html目录，访问文件使用`http://服务器ip:nginx端口/文件地址`的形式访问。

<br>

## 推荐
### EasyWeb管理系统模板
&emsp;一个开箱即用的后台模板，使用简单，模板丰富，包含传统ifram版、spa单页面路由版，[前往查看](https://easyweb.vip)。

<br>