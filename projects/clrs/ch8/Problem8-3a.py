from math import log10, ceil
from itertools import accumulate


def size(x):
    if (x == 1 or x == 0):
        return 1
    return ceil(log10(x))


def radixSort(A):
    if len(A) == 0:
        return A
    xlen = size(A[0])
    # print(f"pre: {A}")
    for i in range(xlen):
        A = countSort(A, lambda x: x // 10 ** i % 10)
        # print(f"post id(A) = {id(A)}")
    # print(f"post: {A}")
    return A


def countSort(A, f):
    # print(f"pre id(A) = {id(A)}")
    range = [0] * 10
    # print(A)
    for x in A:
        range[f(x)] += 1
    range = list(accumulate(range))
    # print(range)
    C = [0]*len(A)
    for x in reversed(A):
        index = f(x)
        # print(range[index])
        C[range[index] - 1] = x
        range[index] -= 1
    # print(f"C = {C}")
    return C


def nSort(A, n):
    buckets = [[] for _ in range(n + 1)]
    # print(buckets)
    for x in A:
        buckets[size(x)].append(x)
    # print(buckets)
    for i, bucket in enumerate(buckets):
        # print(f'pre= {buckets[i]}')
        buckets[i] = radixSort(bucket)
        # print(f'post= {buckets[i]}')
    # print(buckets)
    return [x for bucket in buckets for x in bucket]


def main():
    import random
    n = 10
    k = 1000
    laps = 20
    digits = 0
    A = [] * n
    for _ in range(laps):
        for i in range(n):
            A.append(random.randint(1, k))
            digits += size(A[i])
        A = nSort(A, digits)
        print(all(A[i] >= A[i-1] for i in range(1, len(A))))


if __name__ == "__main__":
    main()
