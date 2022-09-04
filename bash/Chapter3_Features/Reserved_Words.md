#
保留字是对 shell 具有特殊意义的字。 它们用于开始和结束 shell 的复合命令。
#
以下字在不加引号时被识别为保留字，并且是命令的第一个字（见下文例外）：
```
if	    then	elif	else	fi	    time
for	    in	    until	while	do	    done
case	esac	coproc	select	      function
{	    }	    [[	    ]]	       !
```
#
如果 in 是 case 或 select 命令的第三个字，则 in 被识别为保留字。 如果 in 和 do 是 for 命令中的第三个字，则它们被识别为保留字。
