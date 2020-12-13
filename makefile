DATE := $(shell date +"%m/%d/%Y at %H:%M:%S")

.PHONY: git_send
git_send:
	git add *
	git commit -a -m "Automatic commit & push, $(DATE)"
	git push origin master
