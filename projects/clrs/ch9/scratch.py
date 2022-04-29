def findMaxMin(A):
    n = len(A)
    if n % 2:
        maxx = A[0]
        minn = A[0]
        i = 1
    else:
        minn = min(A[0], A[1])
        maxx = max(A[0], A[1])
        i = 2
    for [one, two] in (A[pos:pos + 2] for pos in range(i, n, 2)):
        if one < two:
            small = one
            big = two
        else:
            small = two
            big = one
        minn = min(minn, small)
        maxx = max(maxx, big)
    print(minn, maxx)


def main():
    A = list(range(1, 11))
    findMaxMin(A)


if __name__ == "__main__":
    main()
