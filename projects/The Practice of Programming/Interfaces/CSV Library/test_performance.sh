#!/bin/sh
for tfile in ./test/data/csv/*; do
    echo "Reading from file $tfile:"
	for i in 0 1 2 3; do
		indent="  "
		case "$i" in
		0)
			printf "%sGREEDY: " "$indent"
			;;
		1)
			printf "%sLAZY_ALL: " "$indent"
			;;
		2)
			printf "%sLAZY_UP_TO_N: " "$indent"
			;;
		3)
			printf "%sLAZY_ONLY_N: " "$indent"
			;;
		esac
		/bin/time -f%e cat "$tfile" | ./test_multifield "$i" "0" 1>/dev/null
	done
done
