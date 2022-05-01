#!/bin/sh

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
	/bin/time -p cat './test/data/csv/1000000 Sales Records.csv' | ./test_multifield "$i" "0" 1>/dev/null
done
