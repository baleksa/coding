import subprocess
import random
from sys import argv


def main():
    cname = argv[1]
    name = argv[1][:-2]
    # min_k = 1
    # max_k = 20
    n_min = 10
    n_max = 30
    n = random.randint(n_min, n_max)
    k = random.randint(1, n)
    max_int = 10000
    args = random.sample(range(1, max_int + 1), n)
    args = [str(k), str(n)] + list(map(str, args))
    subprocess.run(f"gcc {cname} -o {name}", shell=True)
    subprocess.run([f"./{name}"] + args, capture_output=False)


if __name__ == "__main__":
    main()
