#!/bin/bash
if test -x a.out; then
	for FILE in examples/CZE/*_in.txt;
	do ./a.out <$FILE | diff --color -u - ${FILE/in/out} ;
	done
	
else
	echo "a.out does not exist or it's not executable"
fi



