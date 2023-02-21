def sortare_insertie(l):
    '''
    Sorteaza lista l
    :param l: list of elements
    :return: sorted list

    Caz favorabil: lista deja sortata, T(n) = n - 1, apartine Teta(n)
    Caz defavorabil: lista invers sortata, T(n) = n(n-1)/2, apartine Teta(n^2)
    Caz mediu: (n^2+3n)/4 - suma de la i = 1 la n de 1/i, apartine Teta(n^2)
    Overall complexity: O(n^2)
    Complexitate spatiu: Teta(1) (algoritm in-place)

    *PASI
    1. se parcurg elementele
    2. se insereaza elementul curent pe pozitia corecta in subsecventa
    deja sortata
    3. in subsecventa ce contine elementele deja sortate se tin
    elementele sortate pe tot parcursul algoritmului, astfel dupa ce
    parcurgem toate leementele secventa este sortata in intregime
    '''
    for i in range(1, len(l)):
        ind = i - 1
        curent_element = l[i]
        #we need to insert a in the right position
        while ind >= 0 and curent_element < l[ind]:
            l[ind + 1] = l[ind]
            ind = ind - 1
        l[ind + 1] = curent_element

def test_sortare_insertie():
    test_list = [1, 5, -2, 3, 4, 7]
    sortare_insertie(test_list)
    assert test_list == [-2, 1, 3, 4, 5, 7]
