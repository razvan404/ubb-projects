def sortare_quick(l):
    '''
    Sorteaza lista l
    :param l: list of elements
    :return: ordered list
    '''
    if len(l) <= 1:
        return l
    pivot = l.pop()
    lesser = sortare_quick([x for x in l if x < pivot])
    greater = sortare_quick([x for x in l if x >= pivot])
    return lesser + [pivot] + greater

def test_sortare_quick():
    test_list = [1, 5, -2, 3, 4, 7]
    assert sortare_quick(test_list) == [-2, 1, 3, 4, 5, 7]
