#!/bin/sh

num=1

cat | while IFS= read -r line; do
				
	if [ $((num%2)) -eq 0 ]; then
		line=$(echo "$line" | tr '[:upper:]' '[:lower:]');	
	else
		line=$(echo "$line" | tr '[:lower:]' '[:upper:]');
	fi
	
	# Если строка состоит только из слова a/an	
	case "$line" in 
		"a"|"an"|"A"|"AN")
	line="";
	;;
	esac
	
	# Если начинается с a/an
	line=$(echo "$line" | sed 's/^[aA][nN]* //');	
	
	case $(echo "$line" | rev | cut -c 1) in 
		[?!.,:\;]) ;;
	*)
		line="$line.";
		;;
	esac

	num=$((num+1));
	echo "$line";
done
