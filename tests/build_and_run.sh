#!/bin/bash

i=0
for t in "da.c ../jak_da.c" "ht.c ../jak_ht.c murmur3.c ../jak_da.c" "l.c ../jak_l.c" "sl.c ../jak_sl.c"
do
	i=$((i+1))
	rm -f test$i
	cc  -Wall -Wextra -pedantic -std=gnu99 -g $t -o test$i
	echo "++++++++++====================++++++++++"
	echo "-----> Running test \"$i\" ..."
	if ./test$i
	then
		echo "**** \"$i\" test succeded :)"
	else
		echo "!!!! \"$i\" test failed :( . Files were: $t"
		exit -1
	fi
	echo "-----> Running valgrind for test \"$i\" ..."
	if valgrind --log-file=$i.valgrind.log --leak-check=full --show-leak-kinds=all --error-exitcode=2 ./test$i \
		&& grep -q "in use at exit: 0 bytes in 0 blocks" $i.valgrind.log
then
	echo "**** Valgrind test succeded"
else
	echo "!!!! Valgrind test failed. Files were: $t"
	exit -2
fi

done

echo "###############################################################"
echo "###############################################################"
echo "##############       ALL TESTS SUCCEEDED :)    ################"
echo "###############################################################"
echo "###############################################################"
