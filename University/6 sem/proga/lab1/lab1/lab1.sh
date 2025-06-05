#!/bin/sh
dir=$1; find $dir -name "*.cmake" | while read -r file; do head -n 5 $file | grep -qi "copyright" && echo $file; done

