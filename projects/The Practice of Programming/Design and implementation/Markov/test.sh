#!/bin/sh
for book in ./test_books/*; do
	title="book '$book':"
	for exe in ./Markov*/*; do
		if [ -x "$exe" ]; then
			time_sec=$(/bin/time 2>&1 -f%e "$exe" <"$book" >/dev/null)
			next_row=$(printf "%-30s took %5.2fs" "$exe" "$time_sec")
			table="$table$next_row\n"
		fi
	done
done
# echo "start${table}end"
table="$(echo "$table" | sort -k3)"
table="$title\n$table"
echo "$table" | tr -s '\n\n' '\n'
