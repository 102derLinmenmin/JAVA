<?php
header("Content-Type: text/html; charset=UTF-8");
if($_POST){
    $name=$_POST['real_name'];
    $age=$_POST['real_age'];
    $province=$_POST['province'];
    $city=$_POST['city'];
    $tel=$_POST['user_tel'];
    $favour=$_POST['favour'];
    $birthday=$_POST['user_birthday'];
    $message=$_POST['message'];
    $favourAll=implode(',',$favour);
}
echo "
<head>
<style type='text/css'>
body{background:url(22.jpg);background-repeat: no-repeat;}
td{text-align:center;}
div{position:absolute;left:50%;top:50%;transform:translate(-50%,-50%);background-color: rgba(245, 255, 250, 0.4);}
</style>
</head>
<body>
<div>
<table width='350' border='1' cellspacing='0' cellpadding='0'>
<tr><td width='130' height='33'>真实姓名</td><td>".$name."</td></tr>
<tr><td width='130' height='33'>真实年龄</td><td>".$age."岁</td></tr>
<tr><td width='130' height='33'>所在地区</td><td>".$province."&nbsp;".$city."</td></tr>
<tr><td width='130' height='33'>手机号码</td><td>".$tel."</td></tr>
<tr><td width='130' height='33'>兴趣爱好</td><td>".$favourAll."</td></tr>
<tr><td width='130' height='33'>出生日期</td><td>".$birthday."</td></tr>
<tr><td width='130' height='33'>网友留言</td><td>".$message."</td></tr>
</div>
</body>"

?>