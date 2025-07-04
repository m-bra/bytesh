#!/bin/bash

path="$HOME/subsys/bin/"

test -z "${3}" || {
	path="${3}"
}

cp "$path/$1" "$path/$2"
