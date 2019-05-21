import subprocess
import sys
import time

if __name__ == "__main__":
    #start = time.time()

    print("n,x,time")

    for i in range(1, 1000):
        start = time.time()
        res = subprocess.run(["./main", str(i)], stdout=subprocess.PIPE)
        # elapsed_time = time.time() - start
        print(f'{i},{res.stdout.decode("utf8")}')
