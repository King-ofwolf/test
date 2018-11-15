#!/bin/bash
function askinput_yn(){
	echo $1
	read flag
	while [[ $flag != yes ]]; do
		if [[ $flag = no ]]; then
			break
		fi
		echo $1
		read flag
	done
}
function colorecho(){
	case $1 in
		(-blue)
			echo -e "\033[32m$2\033[0m"
			:;;
		(-red)
			echo -e "\033[31m$2\033[0m"
			:;;
		(*)
			echo $1
			:;;
	esac
}

function initial(){
	if [[ $# = 0 ]];
	then
		for tag in $(echo -e "dev\ndate")
		do
			colorecho -blue "------checkout -b $tag origin/$tag------"
			git checkout -b $tag origin/$tag
			colorecho -blue "-----------------------------------------"
		done
	else
		for tag in $*
		do
			colorecho -blue "------checkout -b $tag origin/$tag------"
			git checkout -b $tag origin/$tag
			colorecho -blue "-----------------------------------------"
		done
	fi
}
function sync3branch(){
	for tag in $(echo -e "master\ndev\ndate")
	do
		colorecho -blue "------branch $tag push------"
		git checkout $tag
		git push origin $tag
		colorecho -blue "----------------------------"
	done
}
function logs(){
	colorecho -blue "------log --graph --pretty=oneline --abbrev-commit------"
	git log --graph --pretty=oneline --abbrev-commit
	colorecho -blue "----------------------------------------"
}
function recover(){
	colorecho -blue "------Work Directory------"
	colorecho -red "git checkout -- <file name>"
	echo "tips: 1. let the work directory recover to last add or commit state."
	echo "      2. the <file name> needs to be given necessary"
	colorecho -blue "------Stage------"
	colorecho -red "git reset HEAD <file name>"
	echo "tips: 1. under the version of HEAD, push the stage changes back to work directory"
	echo "      2. the <file name> can be ignored"
	colorecho -blue "------remote------"
	colorecho -red "git reset --hard HEAD^"
	colorecho -red "git reset --hard HEAD~n"
	colorecho -red "git reset --hard <commit id>"
	echo "tips: you can use git log or git reflog to see the commit id"
	colorecho -blue "------------------"
}
function branchmerge(){
	colorecho -blue "------merge <branch name>------"
	git merge $1
	colorecho -blue "-------------------------------"
	echo "tips: if merge unsuccessful, change the different place and commit."
}
function dotags(){
	colorecho -blue "------git tag -a <tag> -m <msg> <commit id>------"
	if [ $# = 2 ];
	then
		git tag -a $1 -m $2
	else
		git tag -a $1 -m $2 $3
	fi
	colorecho -blue "-------------------------------------"
}
function synctags(){
	colorecho -blue "------git push origin --tags------"
	git push origin --tags
	colorecho -blue "---------------------------------"
}
function deltags(){
	colorecho -blue "------tag -d <tag>&push origin :refs/tags/<tag>------"
	git tag -d $1
	git push origin :refs/tags/$1
	colorecho -blue "------------------------------------------------"
}
function helpmsg(){
	echo "./mygit.sh [-option] [arg]"
	echo "-h: help massage"
	colorecho -red "<initial>"
	echo "-i: creat branchs and link to remote branch"
	echo "-i [brach name]...: creat [branch name] branchs and link to this remote branch"
	colorecho -red "<sync>"
	echo "-s: sync all 3 branch and all tags to origin remote. including master,dev,date"
	colorecho -red "<log>"
	echo "-l: see logs"
	colorecho -red "<branch merge>"
	echo "-m [branch name]: merge branch <branch name> to this branch"
	colorecho -red "<tag>"
	echo "-t [tag] [msg] [commit id]: add a <tag> to <commitid>"
	echo "-t [tag] [msg]: add a <tag> to this commit"
	echo "-dt [tag]: delete the tag both local remote and origin remote"
	colorecho -red "<recover>"
	echo "-r: see recover message"
	echo "-------------tips-------------"
	echo "pip freeze: list pip package"
}

case $1 in
	(-i)
		shift
		initial $*
		:;;
	(-s)
		shift
		sync3branch
		synctags
		:;;
	(-l)
		logs
		:;;
	(-m)
		shift
		branchmerge $1
		:;;
	(-t)
		shift
		dotags $*
		:;;
	(-dt)
		shift
		deltags $1
		:;;
	(-r)
		recover
		:;;
	(-h) 
		helpmsg
		:;;
	(*)
		cur_path=$(pwd)
		helpmsg
		:;;
esac

# for tag in $*
# do
# 	echo $tag
# done
# --------------------------
# color letter
# "\033[32m 绿色字 \033[0m"