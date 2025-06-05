#!/bin/sh

usage() {
	for msg in "$@"; do printf "%s\n" "${0##*/}: $msg" >&2; done
	echo "usage:${0##*/} content_file name_file price authors" >&2
	exit 1
}

set -e
trap 'echo "Error occured"' ERR

if [ $# -lt 4 ]; then
	usage "missing arguments"
fi

content_file="$1"
name_file="$2"
price="$3"

shift 3

lib_root=$(pwd)

while [ "$lib_root" != "/" ] && [ ! -f "$lib_root/.library" ]; do
	lib_root=$(dirname "$lib_root")
done

if [ -z "$lib_root" ] || [ ! -f "$lib_root/.library" ]; then
	echo "Cannot find library root dir"
	false
fi

if [ ! -f "$content_file" ]; then
	echo "Cannot find content_file"
	false
fi

suff=""
cnt=1

while [ -e "$lib_root/books/${name_file}${suff}" ]; do
	suff=".$cnt"
	cnt=$((cnt+1))
done

name_file="${name_file}${suff}"

tmp_file="$lib_root/.tmp/${name_file}.tmp"
cp "$content_file" "$tmp_file"

mv "$tmp_file" "$lib_root/books/$name_file"
chmod 664 "$lib_root/books/$name_file"

if [ -n "$price" ] && [ "$price" != "-" ]; then
	echo "$price" > "$lib_root/prices/${name_file}.price"
	chmod 644 "$lib_root/prices/${name_file}.price"
fi

for author in "$@"; do
	a_dir="$lib_root/authors/$author"
	if [ ! -d "$a_dir" ]; then
        	mkdir "$a_dir"
        	chmod 755 "$a_dir"
	fi
	
	ln -f "$lib_root/books/$name_file" "$a_dir/$name_file"

done
