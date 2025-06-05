#!/bin/sh

usage() {
	for msg in "$@"; do printf "%s\n" "${0##*/}: $msg" >&2; done
	echo "usage: ${0##*/} start_dir group_name" >&2
	exit 1
}

start_dir="$1"
group="$2"

set -e

trap 'echo "Error occured"' ERR

if [ $# -ne 2 ]; then
	usage "invalid number of arguments"
fi

if [ ! -d "$start_dir" ]; then
	mkdir "$start_dir"
	chmod 755 "$start_dir"
	echo "library v1.0" > "$start_dir/.library"
fi

if [ ! -d "$start_dir/authors" ]; then
	mkdir "$start_dir/authors"
	chmod 755 "$start_dir/authors"
fi

if [ ! -d "$start_dir/books" ]; then
	mkdir "$start_dir/books"
	chmod 755 "$start_dir/books"
fi

if [ ! -d "$start_dir/prices" ]; then
	mkdir "$start_dir/prices"
	chmod 751 "$start_dir/prices"
	chgrp "$group" "$start_dir/prices"
fi

if  [ ! -d "$start_dir/.tmp" ]; then
	mkdir "$start_dir/.tmp"
	chmod 770 "$start_dir/.tmp"
	chgrp "$group" "$start_dir/.tmp"
fi



