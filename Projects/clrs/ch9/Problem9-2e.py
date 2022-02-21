import random


def partition(A, start, end):
    # print("PARTITION():")
    # print(f"start = {start} end = {end}")
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
    # print(f'array: {A} pivot A[{m}] = {A[m]}')
    # print("PARTITION() END")
    return m


def select(A, start, end, ind):
    # print('SELECT():')
    # print(f'select(): start={start} end={end} ind={ind}')
    if start == end:
        # print('SELECT() END')
        return start
    pivot = partition(A, start, end)
    # print(f'select(): start={start} end={end} ind={ind} pivot={pivot}')
    # print('SELECT() END')
    if ind == pivot:
        return pivot
    elif ind > pivot:
        return select(A, pivot + 1, end, ind)
    else:
        return select(A, start, pivot - 1, ind)


def wsum(X, W, sep, start, end):
    val = X[sep]
    lsum, rsum = 0, 0
    # print(W)
    for x in X[start:end + 1]:
        if x < val:
            # print(f'wsum x={x}')
            lsum += W[id(x)]
        elif x > val:
            # print(f'wsum x={x}')
            rsum += W[id(x)]
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
    # print('WMEDIAN():')
    medInd = medianInd(start, end)
    # print(f'medInd: {medInd}')
    pivot = select(A, start, end, medInd)
    lsum, rsum = wsum(A, W, pivot, start, end)
    lsum += lold
    rsum += rold
    # print(f'array: {A}')
    xweight = W[id(A[pivot])]
    # print(f'lsum = {lsum} current = {xweight} rsum = {rsum}')
    # print(f'sum all = {lsum + xweight + rsum}')
    # print('WMEDIAN() end')
    if lsum < 1/2 and rsum <= 1/2:
        return pivot
    if lsum >= 1/2:
        return\
            _weightedMedian(A, W, start, pivot - 1,
                            lold, rsum + W[id(A[pivot])])
    if rsum > 1/2:
        return\
            _weightedMedian(A, W, pivot + 1, end,
                            lsum + W[id(A[pivot])], rold)


def weightedMedian(A, W):
    index = _weightedMedian(A, W, 0, len(A) - 1, 0, 0)
    return index


def getInput():
    n = 11
    sample = range(1, 21)
    xs = random.sample(sample, n)
    ys = random.sample(sample, n)
    ws = random.sample(sample, n)
    ws = list(map(lambda x: x / sum(ws), ws))
    wsx = {id(xs[i]): ws[i] for i in range(n)}
    wsy = {id(ys[i]): ws[i] for i in range(n)}
    return xs, ys, ws, wsx, wsy


def check(W, ind):
    presum, postsum = sum(W[:ind]), sum(W[ind + 1:])
    print(f'presum: {presum} postsum: {postsum}')
    if presum < 1 / 2 and postsum <= 1 / 2:
        print('TRUE')
    else:
        print('FALSE')


def main():
    xs, ys, ws, wsx, wsy = getInput()
    # oxs, oys, ows = xs.copy(), ys.copy(), ws.copy()
    print(f'Points: {list(zip(xs, ys, ws))}')
    print(f'xs: {xs}')
    print(f'ys: {ys}')
    print(f'ws: {ws} sumws: {sum(ws)}')
    wmindx = weightedMedian(xs, wsx)
    print(f'after xs: {xs}')
    wsx = [wsx[id(x)] for x in xs]
    print(f'after ws : {wsx}')
    check(wsx, wmindx)
    wmindy = weightedMedian(ys, wsy)
    print(f'after ys: {ys}')
    wsy = [wsy[id(y)] for y in ys]
    print(f'after ws: {wsy}')
    check(wsy, wmindy)

    print(f'Point: X={xs[wmindx]} Y={ys[wmindy]}')


if __name__ == "__main__":
    main()
