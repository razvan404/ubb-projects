def add(x, y, base):
    '''
    Adună pe x si pe y în baza dată
    :param x: list
    :param y: list
    :param base: int
    :return: list
    '''
    if len(x) > len(y):
        for i in range(len(y), len(x)):
            y.insert(0, 0)
    if len(y) > len(x):
        for i in range(len(x), len(y)):
            x.insert(0, 0)
    t = 0
    z = []
    for i in range(len(x) - 1, -1, -1):
        cat = (x[i] + y[i] + t) // base
        rest = (x[i] + y[i] + t) % base
        z.insert(0, rest)
        t = cat
    z.insert(0, t)
    while len(x) > 1 and x[0] == 0:
        x.pop(0)
    while len(y) > 1 and y[0] == 0:
        y.pop(0)
    while len(z) > 1 and z[0] == 0:
        z.pop(0)
    return z


def decrease(x, y, base):
    '''
    Scade din x pe y în baza dată
    :param x: list
    :param y: list
    :param base: int
    :return: list
    '''
    z = []
    t = 0
    for i in range(len(y), len(x)):
        y.insert(0, 0)
    for i in range(len(x) - 1, -1, -1):
        if x[i] + t >= y[i]:
            z.insert(0, x[i] + t - y[i])
            t = 0
        else:
            z.insert(0, x[i] + t + base - y[i])
            t = -1
    while len(y) > 1 and y[0] == 0:
        y.pop(0)
    while len(z) > 1 and z[0] == 0:
        z.pop(0)
    return z


def multiply(x, y, base):
    '''
    Înmulțește pe x cu o cifră într-o baza dată
    :param x: list
    :param y: int
    :param base: int
    :return: list
    '''
    z = []
    t = 0
    for i in range(len(x) - 1, -1, -1):
        cat = (x[i] * y + t) // base
        rest = (x[i] * y + t) % base
        z.insert(0, rest)
        t = cat
    while t > 0:
        z.insert(0, t % base)
        t = t // base
    while len(z) > 1 and z[0] == 0:
        z.pop(0)
    return z


def divide(x, y, base):
    '''
    Împarte pe x la o cifră într-o bază dată
    :param x: list
    :param y: int
    :param base: int
    :return: [list, int]
    '''
    z = []
    t = 0
    for i in range(0, len(x)):
        cat = (t * base + x[i]) // y
        rest = (t * base + x[i]) % y
        z.append(cat)
        t = rest
    while len(z) > 1 and z[0] == 0:
        z.pop(0)
    return [z, t]

def test_add():
    a = [1, 0, 0, 1, 1, 1, 0, 0, 1]
    b = [1, 0, 0, 0, 1]
    assert (add(a, b, 2) == [1, 0, 1, 0, 0, 1, 0, 1, 0])
    a = [5, 3, 15, 12, 4]
    b = [15, 15, 15]
    assert (add(a, b, 16) == [5, 4, 15, 12, 3])

def test_decrease():
    a = [1, 0, 0, 1, 1, 1, 0, 0, 1]
    b = [1, 0, 0, 0, 1]
    assert (decrease(a, b, 2) == [1, 0, 0, 1, 0, 1, 0, 0, 0])
    a = [5, 3, 15, 12, 4]
    b = [15, 15, 15]
    assert (decrease(a, b, 16) == [5, 2, 15, 12, 5])

def test_multiply():
    a = [1, 2, 0, 1, 2, 1, 0, 0, 1]
    b = 2
    assert (multiply(a, b, 3) == [1, 0, 1, 1, 0, 1, 2, 0, 0, 2])
    a = [5, 3, 15, 12, 4]
    b = 15
    assert (multiply(a, b, 16) == [4, 14, 11, 12, 7, 12])

def test_divide():
    a = [1, 2, 0, 1, 2, 1, 0, 0, 1]
    b = 2
    assert (divide(a, b, 3) == [[2, 1, 2, 1, 0, 1, 1, 2], 0])
    a = [5, 3, 15, 12, 4]
    b = 15
    assert (divide(a, b, 16) == [[5, 9, 9, 5], 9])