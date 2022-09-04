`A phony target is one that is not really the name of a file; rather it is just a name for a recipe to be executed when you make an explicit request.` There are two reasons to use a phony target: `to avoid a conflict with a file of the same name,` and to improve performance.

If you write a rule whose recipe will not create the target file, the recipe will be executed every time the target comes up for remaking. Here is an example:

```
clean:
        rm *.o temp
```

Because the rm command does not create a file named clean, probably no such file will ever exist. Therefore, the rm command will be executed every time you say ‘make clean’.

In this example, `the clean target will not work properly if a file named clean is ever created in this directory. Since it has no prerequisites, clean would always be considered up to date` and its recipe would not be executed. To avoid this problem you can explicitly declare the target to be phony by making it a prerequisite of the special target .PHONY (see Special Built-in Target Names) as follows:

```
.PHONY: clean
clean:
        rm *.o temp
```

Once this is done, ‘make clean’ will run the recipe regardless of whether there is a file named clean.

#


虚假目标是不是真正的文件名的目标。相反，它只是您提出明确请求时要执行的recipe的名称。使用假目标有两个原因：避免与同名文件发生冲突，以及提高性能。

如果您编写了一个规则，其recipe不会创建目标文件，则每次目标出现重新制作时都会执行该recipe。这是一个例子：
```
clean：
        rm *.o temp
```

因为该 `rm` 命令不会创建一个名为 `clean`，可能永远不会存在这样的文件。因此，`rm` 每次都会执行该命令当你指定 `'make clean'`.

在这个例子中，如果一个名为 `clean` 的文件在此目录中创建，目标将无法正常工作。因为没有先决条件，`clean` 将始终被认为是最新的，并且不会执行其 recipe。为避免此问题，您可以通过使其成为 `特殊目标` 的先决条件来显式声明目标是 `.PHONY` ，如下所示：

```
.PHONY：clean
clean：
        rm *.o temp
```
一旦完成，'make clean' 将运行 recipe，无论是否存在名为 clean.

#

# `总结`

如果有和目标相同的文件，又因为文件没有依赖项，所以该文件一定是最新的，为了避免特殊目标和文件重名，使用 .PHONY 来说明该目标是一个 **`is an action not a file`**。  

`使该命令每次都执行`。  

`用于区分文件和命令， 说明该目标是个每次都要执行的命令。`

