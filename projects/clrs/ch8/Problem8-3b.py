import random
import string
from itertools import accumulate

max_range = ord("z") - ord("A") + 1


def getInd(key, item):
    return ord(key(item)) - ord("A")


def countSort(words, start, key, i):
    count = [0] * max_range
    # print(f'words: {words} \nstart = {start} key = {i}')
    for word in words[start:]:
        count[getInd(key, word)] += 1
    count = list(accumulate(count))
    tmp_words = [""] * (len(words) - start)
    for word in reversed(words[start:]):
        index = count[getInd(key, word)] - 1
        tmp_words[index] = word
        count[getInd(key, word)] -= 1
    # print(f'tmp_words: {tmp_words}')
    for i in range(start, len(words)):
        words[i] = tmp_words[i - start]


def nSort(words):
    words.sort(key=len)
    max_len = max([len(x) for x in words])
    indices = [0] * (max_len + 1)
    for word in words:
        indices[len(word)] += 1
    indices = list(accumulate(indices))
    # print(indices)
    for i in range(max_len, 0, -1):
        start = indices[i - 1]
        countSort(words, start, lambda x: x.__getitem__(i - 1), i)


def main():
    k = 10
    n = 20
    words = [
        "".join(
            random.choice(string.ascii_lowercase) for _ in range(random.randint(1, k))
        )
        for _ in range(n)
    ]
    # for i in range(n):
    #     words.append(''.join(random.choice(string.ascii_uppercase
    #                                       + string.digits)
    #                         for _ in range(random.randint(1, k))))
    print(words)
    print(sorted(words))
    nSort(words)
    print(words)
    print(all(words[i] >= words[i - 1] for i in range(1, n)))


if __name__ == "__main__":
    main()
