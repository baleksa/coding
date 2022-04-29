import random
import numpy as np
import time
def hp(A, p, r):
    x = A[p]
    i = p - 1
    j = r + 1
    # print(list(range(len(A))))
    # print(A)
    while True:
        j -= 1
        while A[j] > x:
            j -= 1
        i += 1
        while A[i] < x:
            i += 1
        if i < j:
            tmp = A[i]
            A[i] = A[j]
            A[j] = tmp
            # print(A, " ",f"i = {i} j = {j}")
        else:
            # print(f"i = {i}, j= {j}")
            return j
def quickHoare(A, p, q):
    if (p < q):
        j = hp(A, p, q)
        quickHoare(A, p, j)
        quickHoare(A, j + 1, q)

size = 1000000 
print_len = 25
rng = np.random.default_rng(int(time.time()))
A = rng.integers(low=1, high=1000, size = size)
start = time.time()
quickHoare(A, 0, size - 1)
end = time.time()
for i in range(0, size, size // print_len):
    print(f"{A[i]} ", end="")
print()
if all(A[i] <= A[i+1] for i in range(size -1)):
    print(f"Sorted in {end - start} sec")
