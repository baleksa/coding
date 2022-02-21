import random


def partition(A, start, end):
    print("PARTITION():")
    print(f"start = {start} end = {end}")
    pivoti = random.randint(start, end)
    pivot = A[pivoti]
    A[start], A[pivoti] = A[pivoti], A[start]
    p = start - 1
    m = start
    for j in range(start + 1, end + 1):
        if A[j] == pivot:
            m += 1
            A[m], A[j] = A[j], A[m]
        if A[j] < pivot:
            m += 1
            A[m], A[j] = A[j], A[m]
            p += 1
            A[m], A[p] = A[p], A[m]
    print(f'array: {A} pivot A[{m}] = {A[m]}')
    print("PARTITION() END:")
    return m


def select(A, start, end, ind):
    if start == end:
        return start
    pivot = partition(A, start, end)
    if ind == pivot:
        return pivot
    elif ind > pivot:
        return select(A, pivot + 1, end, ind)
    else:
        return select(A, start, pivot - 1, ind)


def wsum(X, W, sep, start, end):
    val = X[sep]
    lsum, rsum = 0, 0
    for x, w in zip(X[start:end + 1], W[start:end + 1]):
        if x < val:
            lsum += w
        elif x > val:
            rsum += w
    return lsum, rsum


def medianInd(start, end):
    if start == end or end == start + 1:
        return start
    len = end - start + 1
    if len % 2:
        return start + len // 2
    else:
        return start + len // 2 - 1


def _weightedMedian(A, W, start, end, lold, rold):
    print('WMEDIAN():')
    medInd = medianInd(start, end)
    print(f'medInd: {medInd}')
    pivot = select(A, start, end, medInd)
    lsum, rsum = wsum(A, W, pivot, start, end)
    lsum += lold
    rsum += rold
    print(f'array: {A}')
    print(f'lsum = {lsum} rsum = {rsum}')
    print('WMEDIAN() end:')
    if lsum < 1/2 and rsum <= 1/2:
        return pivot
    if lsum >= 1/2:
        return\
            _weightedMedian(A, W, start, pivot - 1, 0, rsum + A[pivot])
    if rsum > 1/2:
        return\
            _weightedMedian(A, W, pivot + 1, end, lsum + A[pivot], 0)


def weightedMedian(A, W):
    index = _weightedMedian(A, W, 0, len(A) - 1, 0, 0)
    return index


def getInput():
    xs = [0.1, 0.25, 0.15, 0.1, 0.15, 0.05, 0.2]
    xs = [0.2] * 5
    ws = xs
    return xs, ws


def main():
    xs, ws = getInput()
    wmind = weightedMedian(xs, ws)
    print(f'xs[{wmind}] = {xs[wmind]}')


if __name__ == "__main__":
    main()
