# Git与GItHub的SSH连接

## 1. 创建SSH密钥 <!-- more -->

```
$>  ssh-keygen -t rsa -C "your_email@example.com"

Generating public/private rsa key pair.
Enter file in which to save the key (...):    <== 回车
                                              <== 设置私有密钥的密码（可直接回车）
                                              <== 再次输入密码
```

## 2. 添加公开密钥
```
$>  cat ~/.ssh/id_rsa.pub                       <== in linux

$>  cat /c/user/yourname/.ssh/id_rsa.pub        <== in windows 
```
> `然后将内容添加到GitHub网页里的SSH Key`

## 3. 尝试连接Github
```
$>  ssh -T git@github.com

    <== yes
    <== 输入私有密钥的密码
```

## 4. 克隆库
```
$>  git clone git@github.com:your_name/repository.git

    <== 输入私有密钥密码
```