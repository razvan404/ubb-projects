def sortare_selectie_directa(l):
    '''
    Sorteaza elementele unei liste
    :param l: list of elements
    :return: ordered list

    T(n) = suma de la i = 1 la n - 1 de suma de la j = i + 1 la n de 1 =
         = n(n - 1)/2 apartine Teta(n^2)

    Algoritmul este in-place (complexitatea spatiu este Teta(1))

    *PASI
    1. la fel ca la sortarea prin selectie normala doar ca se face direct
    '''
    for i in range(0, len(l) - 1):
        for j in range(i + 1, len(l)):
            if l[j] < l[i]:
                l[i], l[j] = l[j], l[i]

def test_sortare_selectie_directa():
    test_list = [1, 5, -2, 3, 4, 7]
    sortare_selectie_directa(test_list)
    assert test_list == [-2, 1, 3, 4, 5, 7]
