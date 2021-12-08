#!/bin/bash
input=(samples/input_*.txt)
count=${#input[@]}
i=0
passed=0
failed=0
for f in "${input[@]}"; do
	i=$((i+1))
	echo Test case $i
	if $1 < samples/input_$i.txt | diff samples/output_$i.txt -; then
		passed=$((passed+1))
	else
		failed=$((failed+1))
	fi
done

echo Passed ${passed}
echo Failed ${failed}
