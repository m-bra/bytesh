#!/bin/bash

path="$HOME/subsys/bin/"

test -z "${1}" || {
	path="${1}"
}

ls "$path/"
