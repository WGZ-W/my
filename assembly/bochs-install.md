# 使用Linux软件管理库进行安装
## 先安装必要的包
```
    sudo apt-get install build-essential xorg-dev libgtk2.0-dev 
```

## 然后安装
```
    sudo apt install bochs
    sudo apt install bochs-x
```
#
#
#

# 使用压缩包进行安装（推荐使用）
## 我使用的是 bochs-2.7.tar.gz
----
## 先进行解压
```
    tar -xzvf bochs-2.7.tar.gz
    cd bochs-2.7
```
## 进行设置需求
```
    ./configure \
    --prefix=/usr/bin/share/bochs \
    --enable-debugger \
    --enable-disasm \
    --enable-iodebug \
    --enable-x86-debugger \
    --with-x \
    --with-x11 \
    LDFLAGS='-pthread' \
    LIBS='-lX11'
```
## 设置没有问题之后编译
```
    make
```

## 编译没有问题之后安装
```
    sudo make install
```

## 卸载（注意在该文件夹中使用命令）
```
    sudo make uninstall 
```
