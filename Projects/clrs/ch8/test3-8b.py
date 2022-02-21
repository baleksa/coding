import string
import subprocess
from random import choice, randint
from sys import argv


def main():
    cname = argv[1]
    name = argv[1][:-2]
    # print(cname, name)
    min_k = 1
    max_k = 20
    k = randint(min_k, max_k)
    n_min = 200
    n_max = 10000
    n = randint(n_min, n_max)
    max_int = 1000
    array = [str(randint(1, max_int)) for _ in range(n)]
    args = [str(n)] + array
    args = args + [str(k)]
    subprocess.run(f"gcc {cname} -o {name}", shell=True)
    subprocess.run([f"./{name}"] + args, capture_output=False)


if __name__ == "__main__":
    main()
