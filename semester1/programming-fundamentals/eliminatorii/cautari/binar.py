def cauta_binar_recursiv(el, l, left, right):
    '''
    Cauta un element intr-o lista
    :param el: elementul cautat
    :param l: lista ordonata
    :param left: primul element al sublistei in care cautam
    :param right: ultimul emenet al sublistei in care cautam
    :return: prima pozitie in care apare elementul sau pozitia unde poate fi inserat
    '''
    if right - left <= 1:
        return right
    m = (left + right) // 2
    if el <= l[m]:
        return cauta_binar_recursiv(el, l, left, m)
    else:
        return cauta_binar_recursiv(el, l, m, right)

def setup_binar_recursiv(el, l):
    '''
    Cauta un element intr-o lista
    :param el: elementul cautat
    :param l: lista ordonata
    :return: pozitia primei aparitii al lui el sau pozitia unde poate fi inserat
    '''
    if len(l) == 0:
        return 0
    if el < l[0]:
        return 0
    if el > l[-1]:
        return len(l)
    return cauta_binar_recursiv(el, l, 0, len(l))

def cauta_binar_iterativ(el, l):
    '''
    Cauta un element intr-o lista
    :param el: elementul cautat
    :param l: lista ordonata
    :return: pozitia primei aparaitii elementului sau pozitia unde poate fi inserat
    '''
    if len(l) == 0:
        return 0
    if el <= l[0]:
        return 0
    if el >= l[-1]:
        return len(l)
    right = len(l)
    left = 0
    while right - left > 1:
        m = (left + right) // 2
        if el <= l[m]:
            right = m
        else:
            left = m
    return right
