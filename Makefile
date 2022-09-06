
.PHONY : commit

commit : 
		git add *
		git commit -m "a"
		git push
		cp /my/note/*.html ~/wgz-w.github.io/
