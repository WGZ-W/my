# 初始设置
```
    git config --global user.name "Firstname Lastname"
    git config --global user.email "your_email@example.com"
```
## 提高命令的可读性
```
    git config --global color.ui auto
```

## 上述命令会在 `"~/gitconfig"` 设置文件
```
    [user]
        name = Firstname Lastname
        email = your_email@example.com
    [color]
        ui = auto
```
windows 上则在用户的目录下有 .gitconfig 文件。

> ## 想要修改这些信息的时候直接编辑这个设置文件
#
#
#

# 设置 SSH Key
## 创建SSH Key
```
    ssh-keygen -t rsa -C "your_email@example.com"
    按下回车
    设置私有密钥的密码（可直接回车）
    再次输入密码
```
## 添加公开密钥
```
    cat ~/.ssh/id_rsa.pub                       in linux
    cat /c/user/yourname/.ssh/id_rsa.pub        in windows
```
> ## 然后将内容添加到GitHub网页里的SSH Key
## 尝试连接Github
```
    ssh -T git@github.com
    yes
    输入私有密钥的密码
```

# 使用GitHub
## 克隆库（下载库）
```
    git clone git@github.com:your_name/repository.git
    输入私有密钥密码
```
克隆出来的文件夹已经连接着远程库可以直接提交
```
    git push -u origin main(根据自己的分支)
    git push
    -u 参数可以在推送的同时，将origin仓库的master分支设置为本地仓库当前分支的upstream（上游）
```
## 远程连接库
```
    git remote add origin git@github.com:your_name/repository.git
    
    origin 可以使用别的名字
```

## 下拉
```
    git pull
```