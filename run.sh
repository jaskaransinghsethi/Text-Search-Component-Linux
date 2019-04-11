#!/bin/sh
# script that tells loader where to find locally defined libraries then runs	
echo "\n"
make -f MakeFile all
./Client.o ./ "*.*" "namespace"

