#!/bin/bash 

export PATH="${PATH}:/singleuserhome/subsys/bin/"

null=/dev/null

test "$1" == "oneline" && {
	mega.status.tray.print > /tmp/mega.status.out
	test "$?" != "0" && {
		printf "MEGA: "
		cat /tmp/mega.status.out | tr '\n' ' ' 
		exit
	}

	d="/singleuserhome/subsys/"
	gith_is_uploaded "${d}" 1>/dev/null 2>&1
	test "$?" != "0" && {
		echo "git not uploaded at ${d}"
		exit
	}

	d="/singleuserhome/JUNEAU/"
	gith_is_uploaded "${d}" 1>/dev/null 2>&1
	test "$?" != "0" && {
		juneau_status="J! "
	}

	printf "%s" "${juneau_status}"
	head -1 "/singleuserhome/status.txt" 

	exit
	
} || {
	echo "MEGA-SYNC"
	echo "========="
	echo
	mega-sync
	echo

	echo "GIT STATUS /singleuserhome/subsys/"
	echo "=========="
	echo
	pushd /singleuserhome/subsys/
	git status | (head ; echo ; echo "..." ; echo ; tail)
	popd

	echo

	ask "Press any key..."
}
