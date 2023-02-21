def sortare_bubble(l):
    '''
    Sorteaza lista
    :param l: list of elements
    :return: sorted list

    Caz favorabil: Teta(n), lista este sortata
    Caz nefavorabil: Teta(n^2), lista este sortata descrescator
    Caz mediu: Teta(n^2)
    Overall complexity: Teta(n^2)
    Complexitate spatiu; Teta(1), algoritm in-place
    '''
    sorted = False
    while not sorted:
        sorted = True # asume de list is sorted
        for i in range(0, len(l) - 1):
            if l[i] > l[i + 1]:
                l[i], l[i + 1] = l[i + 1], l[i]
                sorted = False # the list is not sorted yet

def test_sortare_bubble():
    test_list = [1, 5, -2, 3, 4, 7]
    sortare_bubble(test_list)
    assert test_list == [-2, 1, 3, 4, 5, 7]