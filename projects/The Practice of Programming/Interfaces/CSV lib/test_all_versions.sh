#!/bin/sh

for version in ./*; do
	if [ -d "$version" ]; then
		for file in "$version"/*; do
			if [ -f "$file" ] && [ -x "$file" ]; then
				for test_file in data/csv/*; do
					time_s=$(/bin/time 2>&1 -f%e "$file" <"$test_file" 1>/dev/null)
					echo "$version for $test_file took ${time_s}s."
				done
			fi
		done
	fi
done
