import random


def rangesOverlap(r1, r2):
    return r1[0] <= r2[1] and r2[0] <= r1[1]


def quickFuzzyPartition(A, p, q):
    pivot = random.randint(p, q)
    pivotRange = A[pivot]
    A[pivot], A[p] = A[p], A[pivot]
    i = p - 1
    m = p
    j = p + 1
    while j <= q:
        if rangesOverlap(A[j], pivotRange):
            m += 1
            A[m], A[j] = A[j], A[m]
            pivotRange = (max(A[j][0], pivotRange[0]),
                          min(A[j][1], pivotRange[1]))
        elif A[j][0] < pivotRange[0]:
            smaller = A[j]
            m += 1
            A[j] = A[m]
            i += 1
            A[m] = A[i]
            A[i] = smaller
        j += 1
    return (i+1, m)


def quickFuzzy(A, p, q):
    if (p < q):
        j1, j2 = quickFuzzyPartition(A, p, q)
        quickFuzzy(A, p, j1 - 1)
        quickFuzzy(A, j2 + 1, q)


n = 10
l = 1
r = 100
A = []
for i in range(10):
    a = random.randint(l, r)
    b = random.randint(a, r)
    A.append((a, b))
print(A)
quickFuzzy(A, 0, len(A) - 1)
print(A)
