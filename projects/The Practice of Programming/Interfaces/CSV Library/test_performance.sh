#!/bin/sh
for tfile in ./data/csv/*; do
    echo "Reading from file $tfile:"
	for i in 0 1 2 3; do
		indent="  "
                printf "%s" "$indent"
		case "$i" in
		0)
			printf "GREEDY: "
			;;
		1)
			printf "LAZY_ALL: "
			;;
		2)
			printf "LAZY_UP_TO_N: "
			;;
		3)
			printf "LAZY_ONLY_N: "
			;;
		esac
		/bin/time -f%e cat "$tfile" | ./test_multifield "$i" "$1" 1>/dev/null
	done
done
