#
命令替换重新分配命令 [1] 甚至多个命令的输出； 它实际上将命令输出插入另一个上下文。 [2]
#
```
命令替换的经典形式使用反引号（`...`）。 反引号（反引号）中的命令生成命令行文本。

script_name=`basename $0`
echo "The name of this script is $script_name."
```
#
命令的输出可以用作另一个命令的参数，设置变量，甚至在 for 循环中生成参数列表。
```
rm `cat filename`   # "filename" contains a list of files to delete.
#
# S. C. points out that "arg list too long" error might result.
# Better is              xargs rm -- < filename 
# ( -- covers those cases where "filename" begins with a "-" )

textfile_listing=`ls *.txt`
# Variable contains names of all *.txt files in current working directory.
echo $textfile_listing

textfile_listing2=$(ls *.txt)   # The alternative form of command substitution.
echo $textfile_listing2
# Same result.

# A possible problem with putting a list of files into a single string
# is that a newline may creep in.
#
# A safer way to assign a list of files to a parameter is with an array.
#      shopt -s nullglob    # If no match, filename expands to nothing.
#      textfile_listing=( *.txt )
#
# Thanks, S.C.
```
`命令替换调用子shell。`  
命令替换可能会导致 `word splitting`。
```
COMMAND `echo a b`     # 2 args: a and b

COMMAND "`echo a b`"   # 1 arg: "a b"

COMMAND `echo`         # no arg

COMMAND "`echo`"       # one empty arg


# Thanks, S.C.
```
即使没有 word splitting ，命令替换也可以删除尾随换行符。
```
# cd "`pwd`"  # This should always work.
# However...

mkdir 'dir with trailing newline
'

cd 'dir with trailing newline
'

cd "`pwd`"  # Error message:
# bash: cd: /tmp/file with trailing newline: No such file or directory

cd "$PWD"   # Works fine.





old_tty_setting=$(stty -g)   # Save old terminal setting.
echo "Hit a key "
stty -icanon -echo           # Disable "canonical" mode for terminal.
                             # Also, disable *local* echo.
key=$(dd bs=1 count=1 2> /dev/null)   # Using 'dd' to get a keypress.
stty "$old_tty_setting"      # Restore old setting. 
echo "You hit ${#key} key."  # ${#variable} = number of characters in $variable
#
# Hit any key except RETURN, and the output is "You hit 1 key."
# Hit RETURN, and it's "You hit 0 key."
# The newline gets eaten in the command substitution.

#Code snippet by Stéphane Chazelas.
```
使用 echo 输出带有命令替换的未引用变量集会从重新分配的命令的输出中删除尾随换行符。 这可能会导致令人不快的意外。
```
dir_listing=`ls -l`
echo $dir_listing     # unquoted

# Expecting a nicely ordered directory listing.

# However, what you get is:
# total 3 -rw-rw-r-- 1 bozo bozo 30 May 13 17:15 1.txt -rw-rw-r-- 1 bozo
# bozo 51 May 15 20:57 t2.sh -rwxr-xr-x 1 bozo bozo 217 Mar 5 21:13 wi.sh

# The newlines disappeared.


echo "$dir_listing"   # quoted
# -rw-rw-r--    1 bozo       30 May 13 17:15 1.txt
# -rw-rw-r--    1 bozo       51 May 15 20:57 t2.sh
# -rwxr-xr-x    1 bozo      217 Mar  5 21:13 wi.sh
```
#
命令替换甚至允许使用重定向或 cat 命令将变量设置为文件的内容。
```

variable1=`<file1`      #  Set "variable1" to contents of "file1".
variable2=`cat file2`   #  Set "variable2" to contents of "file2".
                        #  This, however, forks a new process,
                        #+ so the line of code executes slower than the above version.

#  Note that the variables may contain embedded whitespace,
#+ or even (horrors), control characters.

#  It is not necessary to explicitly assign a variable.
echo "` <$0`"           # Echoes the script itself to stdout.
```
```
#  Excerpts from system file, /etc/rc.d/rc.sysinit
#+ (on a Red Hat Linux installation)


if [ -f /fsckoptions ]; then
        fsckoptions=`cat /fsckoptions`
...
fi
#
#
if [ -e "/proc/ide/${disk[$device]}/media" ] ; then
             hdmedia=`cat /proc/ide/${disk[$device]}/media`
...
fi
#
#
if [ ! -n "`uname -r | grep -- "-"`" ]; then
       ktag="`cat /proc/version`"
...
fi
#
#
if [ $usb = "1" ]; then
    sleep 5
    mouseoutput=`cat /proc/bus/usb/devices 2>/dev/null|grep -E "^I.*Cls=03.*Prot=02"`
    kbdoutput=`cat /proc/bus/usb/devices 2>/dev/null|grep -E "^I.*Cls=03.*Prot=01"`
...
fi
```
不要将变量设置为长文本文件的内容，除非您有充分的理由这样做。 不要将变量设置为二进制文件的内容，即使是开玩笑。
#
Example 12-1. Stupid script tricks
```
#!/bin/bash
# stupid-script-tricks.sh: Don't try this at home, folks.
# From "Stupid Script Tricks," Volume I.

exit 99  ### Comment out this line if you dare.

dangerous_variable=`cat /boot/vmlinuz`   # The compressed Linux kernel itself.

echo "string-length of \$dangerous_variable = ${#dangerous_variable}"
# string-length of $dangerous_variable = 794151
# (Newer kernels are bigger.)
# Does not give same count as 'wc -c /boot/vmlinuz'.

# echo "$dangerous_variable"
# Don't try this! It would hang the script.


#  The document author is aware of no useful applications for
#+ setting a variable to the contents of a binary file.

exit 0
```
`请注意，不会发生缓冲区溢出。 这是一个例子，解释型语言（例如 Bash）比编译型语言提供了更多防止程序员错误的保护。`
#
命令替换允许将变量设置为循环的输出。 关键是在循环中获取 echo 命令的输出。  
#
Example 12-2. Generating a variable from a loop
```

#!/bin/bash
# csubloop.sh: Setting a variable to the output of a loop.

variable1=`for i in 1 2 3 4 5
do
  echo -n "$i"                 #  The 'echo' command is critical
done`                          #+ to command substitution here.

echo "variable1 = $variable1"  # variable1 = 12345


i=0
variable2=`while [ "$i" -lt 10 ]
do
  echo -n "$i"                 # Again, the necessary 'echo'.
  let "i += 1"                 # Increment.
done`

echo "variable2 = $variable2"  # variable2 = 0123456789

#  Demonstrates that it's possible to embed a loop
#+ inside a variable declaration.

exit 0
```
```
命令替换使得扩展 Bash 可用的工具集成为可能。 只需编写一个输出到标准输出的程序或脚本（就像一个表现良好的 UNIX 工具一样）并将该输出分配给一个变量。

#include <stdio.h>

/*  "Hello, world." C program  */		

int main()
{
  printf( "Hello, world.\n" );
  return (0);
}

bash$ gcc -o hello hello.c
```
```
#!/bin/bash
# hello.sh		

greeting=`./hello`
echo $greeting

bash$ sh hello.sh
Hello, world.
```
`$(...) 形式已取代命令替换的反引号。`
```
output=$(sed -n /"$1"/p $file)   # From "grp.sh"	example.
	      
# Setting a variable to the contents of a text file.
File_contents1=$(cat $file1)      
File_contents2=$(<$file2)        # Bash permits this also.
```
$(...) 形式的命令替换以不同于 `...` 的方式处理双反斜杠。
```
bash$ echo `echo \\`


bash$ echo $(echo \\)
\
```
$(...) 形式的命令替换允许嵌套。 [3]
```
word_count=$( wc -w $(echo * | awk '{print $8}') )
```
或者，为了更精致的东西。 . .

#
Example 12-3. Finding anagrams
```
#!/bin/bash
# agram2.sh
# Example of nested command substitution.

#  Uses "anagram" utility
#+ that is part of the author's "yawl" word list package.
#  http://ibiblio.org/pub/Linux/libs/yawl-0.3.2.tar.gz
#  http://bash.deta.in/yawl-0.3.2.tar.gz

E_NOARGS=86
E_BADARG=87
MINLEN=7

if [ -z "$1" ]
then
  echo "Usage $0 LETTERSET"
  exit $E_NOARGS         # Script needs a command-line argument.
elif [ ${#1} -lt $MINLEN ]
then
  echo "Argument must have at least $MINLEN letters."
  exit $E_BADARG
fi



FILTER='.......'         # Must have at least 7 letters.
#       1234567
Anagrams=( $(echo $(anagram $1 | grep $FILTER) ) )
#          $(     $(  nested command sub.    ) )
#        (              array assignment         )

echo
echo "${#Anagrams[*]}  7+ letter anagrams found"
echo
echo ${Anagrams[0]}      # First anagram.
echo ${Anagrams[1]}      # Second anagram.
                         # Etc.

# echo "${Anagrams[*]}"  # To list all the anagrams in a single line . . .

#  Look ahead to the Arrays chapter for enlightenment on
#+ what's going on here.

# See also the agram.sh script for an exercise in anagram finding.

exit $?
```

# Notes
[1] 出于命令替换的目的，命令可以是外部系统命令、内置脚本，甚至是脚本函数。
#
[2] 在技术上更正确的意义上，命令替换提取命令的标准输出，然后使用 = 运算符将其分配给变量。
# 
[3] 事实上，使用反引号嵌套也是可能的，但只能通过转义内部反引号，正如 John Default 指出的那样。
```
word_count=` wc -w \`echo * | awk '{print $8}'\` `
```

