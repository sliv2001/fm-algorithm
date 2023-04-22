#!/bin/bash
for filename in ./benchmark_set/*.hgr
do 
#	./build/fm $filename
#	echo
#	echo "Modified"
	./build/fm $filename -m --value 20
	echo
done


