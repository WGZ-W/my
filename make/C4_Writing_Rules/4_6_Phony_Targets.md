# 4.6 Phony Targets

A phony target is one that is not really the name of a file; rather it is just a name for a recipe to be executed when you make an explicit request. There are two reasons to use a phony target: to avoid a conflict with a file of the same name, and to improve performance.
#
虚假目标是不是真正的文件名的目标。 相反，它只是您提出明确请求时要执行的配方的名称。 使用假目标有两个原因：避免与同名文件发生冲突，以及提高性能。
#

If you write a rule whose recipe will not create the target file, the recipe will be executed every time the target comes up for remaking. Here is an example:
#
如果您编写了一个规则，其配方不会创建目标文件，则每次目标出现重新制作时都会执行该配方。 这是一个例子：
```
clean:
        rm *.o temp
```
#

Because the rm command does not create a file named clean, probably no such file will ever exist. Therefore, the rm command will be executed every time you say ‘make clean’.
#
因为 rm 命令不会创建名为 clean 的文件，所以可能永远不会存在这样的文件。 因此，每次您说 "make clean" 时都会执行 rm 命令。
#

In this example, the clean target will not work properly if a file named clean is ever created in this directory. Since it has no prerequisites, clean would always be considered up to date and its recipe would not be executed. To avoid this problem you can explicitly declare the target to be phony by making it a prerequisite of the special target .PHONY (see Special Built-in Target Names) as follows:
#
在此示例中，如果在此目录中创建了名为 clean 的文件，则 clean 目标将无法正常工作。 `因为它没有先决条件，所以 clean 总是被认为是最新的，它的配方不会被执行。` 为避免此问题，您可以通过将其作为特殊目标 .PHONY 的先决条件来显式声明目标是假的（请参阅`特殊内置目标名称`），如下所示：
```
.PHONY: clean
clean:
        rm *.o temp
```
#

Once this is done, ‘make clean’ will run the recipe regardless of whether there is a file named clean.
#
完成此操作后，无论是否存在名为 clean 的文件，"make clean" 都会运行配方。
#

Phony targets are also useful in conjunction with recursive invocations of make (see Recursive Use of make). In this situation the makefile will often contain a variable which lists a number of sub-directories to be built. A simplistic way to handle this is to define one rule with a recipe that loops over the sub-directories, like this:
#
假目标在与 make 的递归调用结合使用时也很有用（请参阅 make 的递归使用）。 在这种情况下，makefile 通常会包含一个变量，该变量列出了许多要构建的子目录。 处理此问题的一种简单方法是使用循环遍历子目录的配方定义一个规则，如下所示：
```
SUBDIRS = foo bar baz

subdirs:
        for dir in $(SUBDIRS); do \
          $(MAKE) -C $$dir; \
        done
```
#

There are problems with this method, however. First, any error detected in a sub-make is ignored by this rule, so it will continue to build the rest of the directories even when one fails. This can be overcome by adding shell commands to note the error and exit, but then it will do so even if make is invoked with the -k option, which is unfortunate. Second, and perhaps more importantly, you cannot take advantage of make’s ability to build targets in parallel (see Parallel Execution), since there is only one rule.
#
然而，这种方法存在问题。 首先，在子生成中检测到的任何错误都会被此规则忽略，因此即使其中一个失败，它也会继续构建其余目录。 这可以通过添加 shell 命令来记录错误并退出来克服，但是即使使用 -k 选项调用 make 也会这样做，这是不幸的。 其次，也许更重要的是，您不能利用 make 并行构建目标的能力（请参阅`并行执行`），因为只有一条规则。
#

By declaring the sub-directories as .PHONY targets (you must do this as the sub-directory obviously always exists; otherwise it won’t be built) you can remove these problems:
#
通过将子目录声明为 .PHONY 目标（您必须这样做，因为子目录显然始终存在；否则将无法构建），您可以消除这些问题：
```
SUBDIRS = foo bar baz

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
        $(MAKE) -C $@

foo: baz
```
#

Here we’ve also declared that the foo sub-directory cannot be built until after the baz sub-directory is complete; this kind of relationship declaration is particularly important when attempting parallel builds.
#
这里我们还声明了 foo 子目录必须等到 baz 子目录完成后才能构建； 在尝试并行构建时，这种关系声明尤其重要。
#

The implicit rule search (see Implicit Rules) is skipped for .PHONY targets. This is why declaring a target as .PHONY is good for performance, even if you are not worried about the actual file existing.
#
对于 .PHONY 目标，会跳过隐式规则搜索（请参阅隐式规则）。 这就是为什么将目标声明为 .PHONY 对性能有好处的原因，即使您并不担心实际存在的文件。
#

A phony target should not be a prerequisite of a real target file; if it is, its recipe will be run every time make goes to update that file. As long as a phony target is never a prerequisite of a real target, the phony target recipe will be executed only when the phony target is a specified goal (see Arguments to Specify the Goals).
#
虚假目标不应该是真实目标文件的先决条件； 如果是，则每次 make 更新该文件时都会运行其配方。 只要虚假目标永远不是真实目标的先决条件，虚假目标配方将仅在虚假目标是指定目标时执行（请参阅指定目标的参数）。
#

Phony targets can have prerequisites. When one directory contains multiple programs, it is most convenient to describe all of the programs in one makefile ./Makefile. Since the target remade by default will be the first one in the makefile, it is common to make this a phony target named ‘all’ and give it, as prerequisites, all the individual programs. For example:
#
虚假目标可能有先决条件。 当一个目录包含多个程序时，将所有程序描述在一个 makefile ./Makefile 中最为方便。 由于默认情况下重新制作的目标将是 makefile 中的第一个目标，因此通常将其设置为名为 "all" 的虚假目标，并将所有单独的程序作为先决条件。 例如：
```
all : prog1 prog2 prog3
.PHONY : all

prog1 : prog1.o utils.o
        cc -o prog1 prog1.o utils.o

prog2 : prog2.o
        cc -o prog2 prog2.o

prog3 : prog3.o sort.o utils.o
        cc -o prog3 prog3.o sort.o utils.o
```
#


Now you can say just ‘make’ to remake all three programs, or specify as arguments the ones to remake (as in ‘make prog1 prog3’). Phoniness is not inherited: the prerequisites of a phony target are not themselves phony, unless explicitly declared to be so.
#
现在您可以只说 "make" 来重新制作所有三个程序，或者将要重新制作的程序指定为参数（如 "make prog1 prog3" ）。 `假性不是继承的：假目标的先决条件本身不是假的，除非明确声明是假的。`
#

When one phony target is a prerequisite of another, it serves as a subroutine of the other. For example, here ‘make cleanall’ will delete the object files, the difference files, and the file program:
#
`当一个虚假目标是另一个的先决条件时，它充当另一个的子程序。` 例如，这里的 "make cleanall" 将删除目标文件、差异文件和文件程序：
```
.PHONY: cleanall cleanobj cleandiff

cleanall : cleanobj cleandiff
        rm program

cleanobj :
        rm *.o

cleandiff :
        rm *.diff
```
#