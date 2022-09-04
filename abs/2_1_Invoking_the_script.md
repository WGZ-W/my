#
编写脚本后，您可以通过 sh scriptname、[1] 或 bash scriptname 调用它。 （不推荐使用 sh < scriptname，因为这有效地禁用了从脚本中的标准输入读取。）更方便的是使用 chmod 使脚本本身直接可执行。
Either:
```
    chmod 555 scriptname (gives everyone read/execute permission) [2]
```
or
```
    chmod +rx scriptname (gives everyone read/execute permission)

    chmod u+rx scriptname (gives only the script owner read/execute permission)
```
使脚本可执行后，您现在可以通过 ./scriptname 对其进行测试。 [3] 如果它以 “sha-bang” 行开头，则调用脚本会调用正确的命令解释器来运行它。
#
作为最后一步，在测试和调试之后，您可能希望将其移动到     /usr/local/bin（当然是以 root 身份），以使您和所有其他用户都可以使用该脚本作为系统范围的可执行文件。 然后可以通过简单地从命令行键入 scriptname [ENTER] 来调用该脚本。

# Notes
[1] 注意：通过 sh scriptname 调用 Bash 脚本会关闭 Bash 特定的扩展，因此脚本可能无法执行。
#
[2] 脚本需要读取以及执行权限才能运行，因为 shell 需要能够读取它。
#
[3] 为什么不简单地用 scriptname 调用脚本呢？ 如果您所在的目录 ($PWD) 是 scriptname 所在的目录，为什么这不起作用？ 这会失败，因为出于安全原因，当前目录 (./) 默认情况下不包含在用户的 $PATH 中。 因此，有必要使用 ./scriptname 显式调用当前目录中的脚本。
