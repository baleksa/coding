#!/bin/sh

echo "Testing with file $1:"
for i in 0 1 2 3; do
	case "$i" in
	0)
		echo "GREEDY:"
		;;
	1)
		echo "LAZY_ALL:"
		;;
	2)
		echo "LAZY_UP_TO_N:"
		;;
	3)
		echo "LAZY_ONLY_N:"
		;;
	esac
	./test_multifield "$i" "1" < "$1"
done
