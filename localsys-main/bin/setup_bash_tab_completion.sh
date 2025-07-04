(return 0 2>/dev/null) || {
	echo "This command must be sourced."
	exit 1
}

#import directive
test "${HOME_LOCAL_BIN_BASHRC_SOURCED}" == "" && {
	echo "Must source \${HOME}/.local/bin/bashrc first"
	return 1
}

#privacy directive
[[ "$(caller.path)" = "${HOME}/.bashrc"* ]] || {
	echo "This command is only executable within: \${HOME}/.bashrc"
	return 1
}

#pathroot=/example/path/
#
#_example_function() {
#	cword=${COMP_WORDS[${COMP_CWORD}]}
#	
#	argdir=$(test "${cword}" != "" && echo $(dirname "${cword}"))
#	argfile=$(test "${cword}" != "" && echo $(basename "${cword}"))
#	suggestions=$(lsA "${pathroot}/${argdir}" | grep "^${argfile}")
#	#suffix=$(test -d "${pathroot}")
#	COMPREPLY=( $(
#		printf %s "${argdir}/" ;
#		printf %s "${suggestions}" ;
#	) )
#}
#
#complete -F _example_function example_function


pathroot="/home/mbrandt/.local/var/lookup/"

_lookup() {
	cword=${COMP_WORDS[${COMP_CWORD}]}
	
	argdir=$(test "${cword}" != "" && echo $(dirname "${cword}"))
	argfile=$(test "${cword}" != "" && echo $(basename "${cword}"))
	suggestions=$(lsA "${pathroot}/${argdir}" | grep "^${argfile}")
	#suffix=$(test -d "${pathroot}")
	COMPREPLY=( $(
		printf %s "${argdir}/" ;
		printf %s "${suggestions}"
	) )
}

complete -F _lookup lookup
