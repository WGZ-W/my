## 10.5.3 Automatic Variables
Suppose you are writing **`a pattern rule`** to compile a ‘.c’ file into a ‘.o’ file: how do you write the ‘cc’ command so that it operates on the right source file name? **You cannot write the name in the recipe**, because the name is different **each time the implicit rule is applied.**

What you do is use a special feature of make, the automatic variables. **These variables have values computed afresh for each rule that is executed, based on the target and prerequisites of the rule.** In this example, you would use `‘$@’` for the object file name and `‘$<’` for the source file name.

It’s very important that you recognize the limited scope in which automatic variable values are available: **`they only have values within the recipe`**. In particular, you cannot use them anywhere within the target list of a rule; they have no value there and will expand to the empty string. Also, they cannot be accessed directly within the prerequisite list of a rule. A common mistake is attempting to use $@ within the prerequisites list; this will not work. However, there is a special feature of GNU make, secondary expansion (see Secondary Expansion), which will allow automatic variable values to be used in prerequisite lists.

Here is a table of automatic variables:

- $@  
```
   The file name of the target of the rule. 
```

- $<
```
    The name of the first prerequisite. 
```

- $^
```
    The names of all the prerequisites, with spaces between them. A target has only one prerequisite on each other file it depends on, no matter how many times each file is listed as a prerequisite. So if you list a prerequisite more than once for a target, the value of $^ contains just one copy of the name. This list does not contain any of the order-only prerequisites; for those see the ‘$|’ variable, below.
```

- $?
```
    The names of all the prerequisites that are newer than the target, with spaces between them. If the target does not exist, all prerequisites will be included.
```

# `总结`
当一个 rules 作为一个模式的时候，target 和 prerequisites 根据使用的命令不同，生成不同命名的文件，此时不能在 recipe 中写出文件的名字。所以要使用这些 automatic variables 。

- $<
  - 第一个 prerequisite 的名字。 
- $^
  - 所有的 prerequisites 的名字，中间用空格隔开。
- $@
  - target 文件的名字。

- $?
  - 所有比 target 新的 prerequisites 的名字，中间用空格隔开
