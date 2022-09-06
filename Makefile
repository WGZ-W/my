
.PHONY : commit

commit : 
		cp /my/note/*.html ~/wgz-w.github.io/
		git add *
		git commit -m "a"
		git push
