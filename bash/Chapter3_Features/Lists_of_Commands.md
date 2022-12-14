#
列表是一个或多个管道的序列，由运算符 “;” 、 “&” 、  “&&” 或 “||” 之一分隔，并可选地以 “;” 、 “&” 或 换行符。
#
在这些列表运算符中， “&&” 和 “||” 具有相同的优先级，其次是 “;” 和 “&” ，它们具有相同的优先级。
#
一个或多个换行符的序列可能出现在列表中以分隔命令，相当于分号。
#
如果命令被控制运算符 “&” 终止，则 shell 在子 shell 中异步执行命令。 这被称为在后台执行命令，这些被称为异步命令。 shell 不等待命令完成，返回状态为 0（真）。 当作业控制未激活时（请参阅作业控制），异步命令的标准输入在没有任何显式重定向的情况下从 /dev/null 重定向。
#
用 ‘;’ 分隔的命令按顺序执行； shell 等待每个命令依次终止。 返回状态是最后执行的命令的退出状态。
#
AND 和 OR 列表是一个或多个管道的序列，分别由控制运算符 “&&” 和 “||” 分隔。 AND 和 OR 列表以左结合性执行。
#
AND 列表具有以下形式
```
command1 && command2
```
当且仅当 command1 返回退出状态为零（成功）时，才会执行 command2。
#
OR 列表具有以下形式
```
command1 || command2
```
当且仅当 command1 返回非零退出状态时，才会执行 command2。
#
AND 和 OR 列表的返回状态是列表中执行的最后一个命令的退出状态。
#
