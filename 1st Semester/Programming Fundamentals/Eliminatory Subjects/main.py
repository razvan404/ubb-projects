if __name__ == '__main__':
    fib = []
    fib[0] = 1
    fib[1] = 1
    for i in range (2, 4045):
        fib[i] = fib[i - 1] + fib[i - 2]

