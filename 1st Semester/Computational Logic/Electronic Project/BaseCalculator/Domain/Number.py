def numberToList(x, base):
    '''
    Transformă un număr sub forma unui string
    într-un număr sub forma unei liste
    :param x: string
    :return: list
    '''
    answer = []
    for i in range(0, len(x)):
        if x[i].isdecimal() is True:
            aux = int(x[i])
        elif x[i].upper() == 'A':
            aux = 10
        elif x[i].upper() == 'B':
            aux = 11
        elif x[i].upper() == 'C':
            aux = 12
        elif x[i].upper() == 'D':
            aux = 13
        elif x[i].upper() == 'E':
            aux = 14
        elif x[i].upper() == 'F':
            aux = 15
        else:
            text = "Numarul " + str(x) + " este invalid, baza maximă este 16"
            raise ValueError(text)
        if aux >= base:
            text = "Numarul " + str(x) + " este invalid, nu este scris în baza " + str(base)
            raise ValueError(text)
        answer.append(aux)
    return answer

def listToNumber(x):
    '''
    Transformă un număr sub forma unei liste
    într-un număr sub forma unui string
    :param x: list
    :return: string
    '''
    y = ""
    for i in x:
        if i == 10:
            i = "A"
        elif i == 11:
            i = "B"
        elif i == 12:
            i = "C"
        elif i == 13:
            i = "D"
        elif i == 14:
            i = "E"
        elif i == 15:
            i = "F"
        if i != 0 or y != "":
            y += str(i)
    if y == "":
        y = "0"
    return y

def compare(x, y):
    '''
    Compară numărul x cu numărul y
    :param x: list
    :param y: list
    :return: -1, 0 or 1
    '''
    while len(x) > 1 and x[0] == 0:
        x.pop(0)
    while len(y) > 1 and y[0] == 0:
        y.pop(0)
    if len(x) > len(y):
        return 1
    elif len(y) > len(x):
        return -1
    else:
        for i in range(0, len(x)):
            if x[i] > y[i]:
                return 1
            elif y[i] > x[i]:
                return -1
    return 0

def test_numberToList():
    assert (numberToList('5FD3c4da', 16) == [5, 15, 13, 3, 12, 4, 13, 10])
    assert (numberToList('12300321', 4) == [1, 2, 3, 0, 0, 3, 2, 1])
    if numberToList('5FD3c4da', 16) == [5, 15, 13, 3, 12, 4, 13, 11]:
        assert False
    try:
        numberToList('5FD3c4daS', 16)
        assert False
    except ValueError:
        assert True

    try:
        numberToList('12300321', 3)
        assert False
    except ValueError:
        assert True

def test_listToNumber():
    assert (listToNumber([5, 15, 13, 3, 12, 4, 13, 10]) == '5FD3C4DA')
    assert (listToNumber([1, 2, 3, 0, 0, 3, 2, 1]) == '12300321')

def test_Compare():
    assert (compare([5, 15, 13, 3, 12, 4, 13], [5, 15, 13, 3, 12, 4]) == 1)
    assert (compare([11, 13, 15, 15, 3], [10, 13, 15, 15, 3]) == 1)
    assert (compare([10, 13, 15, 15, 4], [10, 13, 15, 15, 5]) == -1)
    assert (compare([11, 5, 5, 15, 12], [11, 5, 5, 15, 12]) == 0)