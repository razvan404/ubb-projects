from Domain.Number import listToNumber
from Domain.Operations import divide, add, multiply


def silentConvertUsingSuccesiveDivisions(x, oldBase, newBase):
    '''
    Acesta este algoritmul de convertire prin împărțiri succesive
    a lui x din baza *oldBase* în baza *newBase*
    :param x: list
    :param oldBase: integer
    :param newBase: integer
    :return: list
    '''
    result = []
    while listToNumber(x) != '0':
        cat = divide(x, newBase, oldBase)[0]
        rest = divide(x, newBase, oldBase)[1]
        x = cat
        result.append(rest)
    result.reverse()
    return result


def silentConvertUsingSubstitution(x, oldBase, newBase):
    '''
    Acesta este algoritmul de convertire prin substituție
    a lui x din baza *oldBase* în baza *newBase*
    :param x: list
    :param oldBase: integer
    :param newBase: integer
    :return: list
    '''
    result = []
    p = [1]
    for i in range(len(x) - 1, -1, -1):
        a = multiply(p, x[i], newBase)
        result = add(result, a, newBase)
        p = multiply(p, oldBase, newBase)
    return result


def silentConvert(x, oldBase, newBase):
    '''
    Acesta este algoritmul de convertire printr-o bază intermediară
    a lui x din baza *oldBase* în baza *newBase*
    :param x: list
    :param oldBase: integer
    :param newBase: integer
    :return: list
    '''
    if oldBase > newBase:
        r = silentConvertUsingSuccesiveDivisions(x, oldBase, 10)
        return silentConvertUsingSubstitution(r, 10, newBase)
    else:
        r = silentConvertUsingSubstitution(x, oldBase, 10)
        return silentConvertUsingSuccesiveDivisions(r, 10, newBase)


def test_ConvertUsingSuccesiveDivisions():
    assert (silentConvertUsingSuccesiveDivisions([8, 0, 4, 15, 15, 10], 16, 6) == [5, 0, 0, 1, 2, 2, 5, 3, 4])
    assert (silentConvertUsingSuccesiveDivisions([3, 3, 2, 7], 9, 2) == [1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1])
    assert (silentConvertUsingSuccesiveDivisions([3, 0, 3, 2, 3, 1, 0], 5, 3) == [2, 1, 1, 1, 0, 2, 2, 2, 1, 0])

def test_ConvertUsingSubstitution():
    assert (silentConvertUsingSubstitution([5, 0, 0, 1, 2, 2, 5, 3, 4], 6, 16) == [8, 0, 4, 15, 15, 10])
    assert (silentConvertUsingSubstitution([1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1], 2, 9) == [3, 3, 2, 7])
    assert (silentConvertUsingSubstitution([2, 1, 1, 1, 0, 2, 2, 2, 1, 0], 3, 5) == [3, 0, 3, 2, 3, 1, 0])

def test_ConvertUsingCustomBase():
    assert (silentConvert([5, 0, 0, 1, 2, 2, 5, 3, 4], 6, 16) == [8, 0, 4, 15, 15, 10])
    assert (silentConvert([8, 0, 4, 15, 15, 10], 16, 6) == [5, 0, 0, 1, 2, 2, 5, 3, 4])
    assert (silentConvert([1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1], 2, 9) == [3, 3, 2, 7])
    assert (silentConvert([3, 3, 2, 7], 9, 2) == [1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1])
    assert (silentConvert([2, 1, 1, 1, 0, 2, 2, 2, 1, 0], 3, 5) == [3, 0, 3, 2, 3, 1, 0])
    assert (silentConvert([3, 0, 3, 2, 3, 1, 0], 5, 3) == [2, 1, 1, 1, 0, 2, 2, 2, 1, 0])
