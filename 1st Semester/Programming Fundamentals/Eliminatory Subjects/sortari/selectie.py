def sortare_selectie(l):
    '''
    Sorteaza elementele listei
    :param l: list of elements
    :return: ordered list

    Complexitate timp: Teta(n^2)
    Complexitate spatiu: Teta(1) (algoritm in-place)

    *PASI
    1. se determina elementul avand cea mai mica cheie,
    interschimbare elementul cu elementul de pe prima pozitie
    2. reluat procedura pentru restul de elemente pana cand
    toate elementele au fost considerate
    '''
    for i in range(0, len(l) - 1):
        ind = i
        #cautam cel mai mic element in restul listei
        for j in range(i + 1, len(l)):
            if l[j] < l[ind]:
                ind = j
        l[i], l[ind] = l[ind], l[i]

def test_sortare_selectie():
    test_list = [1, 5, -2, 3, 4, 7]
    sortare_selectie(test_list)
    assert test_list == [-2, 1, 3, 4, 5, 7]
