## 3.2 What Name to Give Your Makefile
By default, when make looks for the makefile, it tries the following names, in order: GNUmakefile, makefile and Makefile.

Normally you should call your makefile either makefile or Makefile. (We recommend Makefile because it appears prominently near the beginning of a directory listing, right near other important files such as README.) The first name checked, GNUmakefile, is not recommended for most makefiles. You should use this name if you have a makefile that is specific to GNU make, and will not be understood by other versions of make. Other make programs look for makefile and Makefile, but not GNUmakefile.

If make finds none of these names, it does not use any makefile. Then you must specify a goal with a command argument, and make will attempt to figure out how to remake it using only its built-in implicit rules. See Using Implicit Rules.

If you want to use a nonstandard name for your makefile, you can specify the makefile name with the ‘-f’ or ‘--file’ option. The arguments ‘-f name’ or ‘--file=name’ tell make to read the file name as the makefile. If you use more than one ‘-f’ or ‘--file’ option, you can specify several makefiles. All the makefiles are effectively concatenated in the order specified. The default makefile names GNUmakefile, makefile and Makefile are not checked automatically if you specify ‘-f’ or ‘--file’.

## `推荐使用 Makefile 作为 name，因为它出现在目录列表开头附近的显眼位置，就在其他重要文件（如 README）附近。若使用 -f 选项，则默认的 Makefile 和 makefile 不会自动检测。`