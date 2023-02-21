def cauta_succesiv_neordonat(el, l):
    '''
    Cauta prima aparitie a unui element intr-o lista
    :param el: element
    :param l: lista de elemente
    :return: pozitia elementului sau -1 altfel

    Best case: (the element is first): T(n) = 1
    Worst case: (the element is last): T(n) = suma de la i = 0 la n - 1 de 1 = n
    Average complexity: (1 + 2 + ... + n)/n = (n+1)/2
    Overall complexity: O(n)
    '''
    i = 0
    while i < len(l) and el != l[i]:
        i += 1
    if i < len(l):
        return i
    return -1

def cauta_succesiv_ordonat(el, l):
    '''
    Cauta prima aparitie a unui element intr-o lista sau pozitia unde poate fi inserat
    :param el: element
    :param l: lista de elemente ordonate crescator
    :return: pozitia primei aparitii sau pozitia unde elementul poate fi inserat

    Best case: (the list is empty): T(n) = 1
    Worst case: (the element is not in the list): T(n) = suma de la i = 0 la n de 1 = n + 1
    Average complexity: (1 + 2 + ... + n + 1)/n
    Overall complexity: O(n)
    '''
    if len(l) == 0:
        return 0
    if el <= el[0]:
        return 0
    if el >= l[- 1]:
        return len(l)
    i = 0
    while el > l[i] and i < len(l):
        i += 1
    return i