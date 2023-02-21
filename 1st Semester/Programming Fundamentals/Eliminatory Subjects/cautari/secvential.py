def cauta_secvential_neordonat(el, l):
    '''
    Cauta ultima aparitie a unui element intr-o lista
    :param el: element
    :param l: lista de elemente
    :return: pozitia elementului sau -1 altfel

    T(n) = suma de la i = 0 la n-1 din 1 = n apartine Teta(n)
    '''
    poz = -1
    for i in range(0, len(l)):
        if el == l[i]:
            poz = i
    return poz

def cauta_secvential_ordonat(el, l):
    '''
    Cauta ultima aparitie a unui element intr-o lista sau pozitia unde poate fi inserat
    :param el: element
    :param l: lista de elemente ordonate crescator
    :return: pozitia ultimei aparitii sau pozitia unde elementul poate fi inserat

    T(n) = suma de la i = 0 la n-1 din 1 = n apartine Teta(n)
    '''
    if len(l) == 0:
        return 0
    poz = -1
    for i in range(0, len(l)):
        if el <= l[i]:
            poz = i
    if poz == -1:
        return len(l)
    return poz
