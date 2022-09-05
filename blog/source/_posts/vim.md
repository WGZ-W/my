---
title: vim
date: 2022-09-05 12:29:40
tags:
---


<!-- more -->

## Search and replace
```
    :s/foo/bar    
    
    :s/foo/bar/g    匹配到的单词全部替换

    :s/foo/bar/gi   大小写敏感
    
    :4,8s/foo/bar/g
    
    :%s/foo/bar/g   整个文件
    
    :1,$s/foo/bar/g 整个文件
```

## Reading input
```
    :r fname    读入文件

    :r !ls      读入命令的结果

    :r          读入当前文件
```

## Multiple files
```
    :n      编辑下一个文件

    :rew    回到第一个文件

    :args   列出打开的文件，标记出正在使用的文件
```

## Setting options(.vimrc)
```
    set number

    set relativenumber  设置相对的行号（比较nb）

    
```

