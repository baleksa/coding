import random
import time


def partition(A, p, q):
    pivot = random.randint(p, q)
    x = A[pivot]

    # print(f"pivot={A[pivot]}")
    # print(A[p:q+1])

    tmp = A[pivot]
    A[pivot] = A[p]
    A[p] = tmp

    i = p - 1
    m = p
    j = p + 1
    # print(f"i={i} m={m} j={j}")
    while j <= q:
        if A[j] < x:
            smaller = A[j]
            m += 1
            A[j] = A[m]
            i += 1
            A[m] = A[i]
            A[i] = smaller
        elif A[j] == x:
            m += 1
            tmp = A[m]
            A[m] = A[j]
            A[j] = tmp
        # print(A[p:j+1], f" i={i} m={m} j={j}")
        j += 1
    # print(f"p={p} q={q}")
    # print(f"i+1={i+1} m={m}")
    # print(f"A[{i + 1}] = {A[i + 1]}, A[{m}] = {A[m]}")
    # print(A[p:q+1])
    # print("------------------------------")
    return i + 1, m


def quickSort(A, p, q):
    if (p < q):
        j1, j2 = partition(A, p, q)
        quickSort(A, p, j1 - 1)
        quickSort(A, j2 + 1, q)


A = random.sample(range(1, 1000), 200) * 4 + random.sample(range(1, 1000), 999)
# A = [13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21]
# A = [9, 5, 12, 8, 7, 4, 11, 2, 6]


n = len(A)
print(f"len(A)={n}")
print("A = ", A)
# for i,x in enumerate(A):
#     print(f"{i}:{x}, ", end="")
# print("\n------------------------------")
start = time.time()
quickSort(A, 0, n - 1)
end = time.time()
if all(A[i] <= A[i+1] for i in range(n - 1)):
    print(f"Sorted in {end - start} sec")
# for i,x in enumerate(A):
#     print(f"{i}:{x}, ", end="")
# print("\n------------------------------")
print("A = ", A)
