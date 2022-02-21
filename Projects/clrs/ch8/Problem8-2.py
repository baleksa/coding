import random


def sort(A, k):
    C = [0] * k
    for a in A:
        C[a - 1] += 1
    for i in range(1, k):
        C[i] += C[i-1]

    B = [0] + C[:-1]
    print(C)
    print(B)
    for i in range(0, len(A)):
        while B[A[i] - 1] != C[A[i] - 1]:
            key = A[i]
            A[i], A[C[key - 1] - 1] = A[C[key - 1] - 1], A[i]
            while(A[C[key - 1] - 1] == key):
                C[key - 1] -= 1


def main():
    k = 5
    n = 10
    A = [random.randint(1, k) for i in range(n)]
    print(A)
    sort(A, k)
    print(A)


if __name__ == "__main__":
    main()
