import random


def sort(A, k):
    C = [0] * k
    for a in A:
        C[a - 1] += 1
    for i in range(1, k):
        C[i] += C[i - 1]
    B = [0] + C[:-1]
    # print(C)
    # print(B)
    for i in range(len(A)):
        while B[A[i] - 1] != C[A[i] - 1]:
            key = A[i]
            A[i], A[C[key - 1] - 1] = A[C[key - 1] - 1], A[i]
            while A[C[key - 1] - 1] == key:
                C[key - 1] -= 1


def main():
    n = 20
    k = 6
    test = []
    for i in range(n):
        for j in range(k):
            A = [random.randint(1, k) for i in range(n)]
            print(A)
            sort(A, k)
            print(A)
            test.append(all(A[i] <= A[i + 1] for i in range(n - 1)))
    print(all(x for x in test))
    print(test)


if __name__ == "__main__":
    main()
