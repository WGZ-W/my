
To allow make to find a customary method for updating a target file, all you have to do is `refrain` from specifying recipes yourself. Either write a rule with no recipe, or don’t write a rule at all. Then make will figure out which implicit rule to use based on which kind of source file exists or can be made.

#
为了让 make 找到更新目标文件的惯用方法，您所要做的就是避免自己指定配方。 `要么写一个没有配方的规则，要么根本不写一个规则。 然后 make 将根据存在或可以制作的源文件类型来确定使用哪个隐式规则。`
#

For example, suppose the makefile looks like this:
#
例如，假设生成文件如下所示：
```
foo : foo.o bar.o
        cc -o foo foo.o bar.o $(CFLAGS) $(LDFLAGS)
```
#

Because you mention foo.o but do not give a rule for it, make will automatically look for an implicit rule that tells how to update it. This happens whether or not the file foo.o currently exists.
#
`因为你提到了 foo.o 但没有给它一个规则，所以 make 会自动寻找一个隐含的规则来告诉如何更新它`。 无论文件 foo.o 当前是否存在，都会发生这种情况。
#

If an implicit rule is found, it can supply both a recipe and one or more prerequisites (the source files). You would want to write a rule for foo.o with no recipe if you need to specify additional prerequisites, such as header files, that the implicit rule cannot supply.
#
如果找到一个隐式规则，它可以提供一个配方和一个或多个先决条件（源文件）。 如果您需要指定隐式规则无法提供的附加先决条件（例如头文件），则您可能希望为 foo.o 编写不带配方的规则。
#

Each implicit rule has a target pattern and prerequisite patterns. There may be many implicit rules with the same target pattern. For example, numerous rules make ‘.o’ files: one, from a ‘.c’ file with the C compiler; another, from a ‘.p’ file with the Pascal compiler; and so on. The rule that actually applies is the one whose prerequisites exist or can be made. So, if you have a file foo.c, make will run the C compiler; otherwise, if you have a file foo.p, make will run the Pascal compiler; and so on.
#
每个隐式规则都有一个目标模式和先决条件模式。 可能有许多具有相同目标模式的隐含规则。 例如，许多规则生成 ".o"文件：一个，使用 C 编译器从 ".c" 文件； 另一个，来自带有 Pascal 编译器的 ".p" 文件； 等等。 实际适用的规则是先决条件存在或可以制定的规则。 所以，如果你有一个文件 foo.c，make 将运行 C 编译器； 否则，如果你有一个文件 foo.p，make 将运行 Pascal 编译器； 等等。
#

Of course, when you write the makefile, you know which implicit rule you want make to use, and you know it will choose that one because you know which possible prerequisite files are supposed to exist. See Catalogue of Built-In Rules, for a catalogue of all the predefined implicit rules.
#
当然，当您编写 makefile 时，您知道要使用哪个隐式规则，并且您知道它将选择那个，因为您知道应该存在哪些可能的先决条件文件。 有关所有预定义隐式规则的目录，请参阅`内置规则目录`。
#

Above, we said an implicit rule applies if the required prerequisites “exist or can be made”. A file “can be made” if it is mentioned explicitly in the makefile as a target or a prerequisite, or if an implicit rule can be recursively found for how to make it. When an implicit prerequisite is the result of another implicit rule, we say that chaining is occurring. See Chains of Implicit Rules.
#
上面，我们说过，如果所需的先决条件 "存在或可以实现"，则适用隐含规则。 如果在 makefile 中明确提到文件作为目标或先决条件，或者如果可以递归地找到如何制作它的隐式规则，则文件 "可以制作"。 当一个隐含的先决条件是另一个隐含规则的结果时，我们说正在发生链接。 请参阅`隐式规则链`。
#

In general, make searches for an implicit rule for each target, and for each double-colon rule, that has no recipe. A file that is mentioned only as a prerequisite is considered a target whose rule specifies nothing, so implicit rule search happens for it. See Implicit Rule Search Algorithm, for the details of how the search is done.
#
通常，为每个目标搜索一个隐式规则，并为每个没有配方的双冒号规则搜索。 仅作为先决条件提及的文件被视为其规则未指定任何内容的目标，因此对其进行隐式规则搜索。 有关如何完成搜索的详细信息，请参阅`隐式规则搜索算法。`
#

Note that explicit prerequisites do not influence implicit rule search. For example, consider this explicit rule:
#
请注意，显式先决条件不会影响隐式规则搜索。 例如，考虑这个明确的规则：
```
foo.o: foo.p
```
#

The prerequisite on foo.p does not necessarily mean that make will remake foo.o according to the implicit rule to make an object file, a .o file, from a Pascal source file, a .p file. For example, if foo.c also exists, the implicit rule to make an object file from a C source file is used instead, because it appears before the Pascal rule in the list of predefined implicit rules (see Catalogue of Built-In Rules).
#
foo.p 的先决条件并不一定意味着 make 将根据隐式规则重新制作 foo.o，以从 Pascal 源文件、.p 文件生成目标文件、.o 文件。 例如，如果 foo.c 也存在，则使用从 C 源文件生成目标文件的隐式规则，因为它出现在预定义隐式规则列表中的 Pascal 规则之前（请参阅`内置规则目录`） .
#

If you do not want an implicit rule to be used for a target that has no recipe, you can give that target an empty recipe by writing a semicolon (see Defining Empty Recipes).
#
`如果您不希望将隐式规则用于没有配方的目标，则可以通过编写分号为该目标指定一个空配方`（请参阅`定义空配方`）。
#