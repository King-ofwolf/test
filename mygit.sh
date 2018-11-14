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

function initial(){
	if [[ $# = 0 ]];
	then
		for tag in $(echo -e "dev\ndate")
		do
			echo "------checkout -b $tag origin/$tag------"
			git checkout -b $tag origin/$tag
			echo "-----------------------------------------"
		done
	else
		for tag in $*
		do
			echo "------checkout -b $tag origin/$tag------"
			git checkout -b $tag origin/$tag
			echo "-----------------------------------------"
		done
	fi
}
function sync3branch(){
	for tag in $(echo -e "master\ndev\ndate")
	do
		echo "------branch $tag push------"
		git checkout $tag
		git push origin $tag
		echo "----------------------------"
	done
}
case $1 in
	-h) 
		echo "./mygit.sh [-h]"
		echo "-h: help massage"
		echo "-i: creat branchs and link to remote branch"
		echo "    -i [brach name]..."
		echo "-------------tips-------------"
		echo "pip freeze: list pip package"
		:;;
	-i)
		shift
		initial $*
		:;;
	-s)
		shift
		sync3branch $*
		:;;
	*)
		cur_path=$(pwd)
		:;;
esac

# for tag in $*
# do
# 	echo $tag
# done
