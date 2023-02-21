def cmp(a, b, cmp_key):
    if cmp_key == '<':
        return a < b
    elif cmp_key == 'date':
        if a.get_publish_date()[2] < b.get_publish_date()[2]:
            return True
        elif a.get_publish_date()[2] > b.get_publish_date()[2]:
            return False
        elif a.get_publish_date()[1] < b.get_publish_date()[1]:
            return True
        elif a.get_publish_date()[1] > b.get_publish_date()[1]:
            return False
        else:
            return a.get_publish_date()[0] <= b.get_publish_date()[0]

def bubble(the_list, cmp_key):
    '''
    Sorteaza elementele listei
    :param the_list: list of elements
    :param cmp_key: compare key
    :return: ordered list
    '''
    sorted = False
    while sorted is False:
        sorted = True
        for i in range(0, len(the_list) - 1):
            if cmp(the_list[i], the_list[i + 1], cmp_key) is False:
                the_list[i], the_list[i + 1] = the_list[i + 1], the_list[i]
                sorted = False
