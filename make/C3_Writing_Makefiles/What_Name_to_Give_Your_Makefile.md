#
`默认情况下，当 make 查找 makefile 时，它会依次尝试以下名称：GNUmakefile、makefile 和 Makefile。`
#
通常你应该调用你的 makefile 或者 makefile 或者Makefile。 `（我们推荐 Makefile，因为它出现在目录列表的开头附近，就在其他重要文件（如 README）附近。）` 检查的名字 GNUmakefile 不建议用于大多数 makefile。 如果您有一个特定于 GNU make 的 makefile，并且不会被其他版本的 make 理解，您应该使用这个名称。 其他 make 程序寻找 makefile 和 Makefile，但不是 GNUmakefile。
#
如果 make 没有找到这些名称，它就不会使用任何 makefile。 然后您必须使用命令参数指定目标，make 将尝试找出如何仅使用其内置的隐式规则来重新制作它。 请参阅使用隐式规则。
#
如果你想为你的 makefile 使用一个非标准的名字，你可以使用 ‘-f’ 或 ‘--file’ 选项来指定 makefile 的名字。 参数 “-f name” 或 “--file=name” 告诉 make 将该文件作为 makefile。 如果您使用多个 “-f” 或 “--file” 选项，则可以指定多个 makefile。 所有的 makefile 都按照指定的顺序有效地连接起来。 `如果您指定 “-f” 或 “--file” ，则不会自动检查默认的 makefile 名称 GNUmakefile、makefile 和 Makefile。`
#

