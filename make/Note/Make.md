## 基本语法
```
    目标 ： 依赖
    （Tab）命令
```

## 通配符
```
    %.bin:%.asm
        Nasm $< -o $@
        
    % 表示匹配任意的 bin 或者 asm 文件
    $< 表示输入文件即 %.asm
    $@ 表示输出文件即 %.bin
```

## .PHNOY（不懂）