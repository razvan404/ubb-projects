def cmp(a, b, key):
    '''
    Compara 2 elemente dupa o cheie
    :param a: object
    :param b: object
    :param key: comparation key
    :return: True / False, care-i mai mare
    '''
    if key == None:
        return a > b
    elif key == 'word':
        return a.get_word() > b.get_word()
    elif key == 'source word':
        return a.get_source().get_word() > b.get_source().get_word()

def bubble(list, key):
    '''
    Bubble sort, sorteaza lista dupa cheie
    :param list: list of objects
    :param key: comparation key
    :return: -
    '''
    sorted = True
    while sorted:
        sorted = False
        for i in range(len(list) - 1):
            if cmp(list[i], list[i + 1], key):
                list[i], list[i + 1] = list[i + 1], list[i]
                sorted = True
