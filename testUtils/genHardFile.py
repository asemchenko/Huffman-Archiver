#! /usr/bin/python3

# function which calculates Fibonacchi range value by it's index
def fib(n):
    if "f" not in dir(fib):
        fib.f = [0,1]
    while n >= len(fib.f):
        fib.f.append(fib.f[-1] + fib.f[-2])
    return fib.f[n]

if __name__ == "__main__":
    from sys import argv
    if len(argv) != 3:
        print("Usage: <filename> <n>")
        exit(1)
    filename = argv[1]
    try:
        n = int(argv[2])
    except:
        print("Can not convert " + argv[2] + " to integer")
        exit(1)
    with open(filename, "wb") as f:
        for i in range(1, n+1):
            f.write(bytes([i]) * fib(i))
