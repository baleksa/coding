import random

# print(sorted([random.randint(1, 15) for _ in range(10)]))


def trans(matrix):
    zipped_rows = zip(*matrix)
    return [list(row) for row in zipped_rows]


def sortColumn(matrix):
    tmp = trans(matrix)
    for row in tmp:
        row.sort()
    tmp = trans(tmp)
    return tmp


def do1(matrix):
    return sortColumn(matrix)


def do13(matrix):
    pm(do1(matrix))


def pm(matrix):
    for row in matrix:
        print(row)


def ps():
    print("-----")


matrix = [[random.choice([0, 1]) for _ in range(3)] for _ in range(6)]
pm(matrix)
ps()
pm(sortColumn(matrix))
