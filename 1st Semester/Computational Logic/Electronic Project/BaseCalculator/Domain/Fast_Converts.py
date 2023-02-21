def showGroups(x):
    '''
    Afișăm grupulețele împărțite printr-o bară
    :param x: list of lists
    :return: string
    '''
    t = "|"
    for i in x:
        for j in i:
            if j == 10:
                t += "A"
            elif j == 11:
                t += "B"
            elif j == 12:
                t += "C"
            elif j == 13:
                t += "D"
            elif j == 14:
                t += "E"
            elif j == 15:
                t += "F"
            else:
                t += str(j)
        t += "|"
    return t

def makeGroups(x, ord):
    '''
    Împarte numărul în grupe de câte *ord*
    :param x: list of integers
    :param ord: int
    :return: list of lists
    '''
    groups = []
    for i in range(0, len(x)):
        if i % ord == 0:
            groups.append([x[i]])
        else:
            groups[-1].append(x[i])
    return groups

def from2toPower(groups, power):
    '''
    Transformă fiecare grupuleț în câte un singur
    număr, corespunzător tabelelor de conversie
    rapidă din baza 2 în baza 2 la puterea *power*
    :param groups: list of lists
    :param power: integer
    :return: list of lists
    '''
    if power == 2:
        for i in range(0, len(groups)):
            if groups[i] == [0, 0]:
                groups[i] = [0]
            elif groups[i] == [0, 1]:
                groups[i] = [1]
            elif groups[i] == [1, 0]:
                groups[i] = [2]
            elif groups[i] == [1, 1]:
                groups[i] = [3]
    if power == 3:
        for i in range(0, len(groups)):
            if groups[i] == [0, 0, 0]:
                groups[i] = [0]
            elif groups[i] == [0, 0, 1]:
                groups[i] = [1]
            elif groups[i] == [0, 1, 0]:
                groups[i] = [2]
            elif groups[i] == [0, 1, 1]:
                groups[i] = [3]
            elif groups[i] == [1, 0, 0]:
                groups[i] = [4]
            elif groups[i] == [1, 0, 1]:
                groups[i] = [5]
            elif groups[i] == [1, 1, 0]:
                groups[i] = [6]
            elif groups[i] == [1, 1, 1]:
                groups[i] = [7]
    if power == 4:
        for i in range(0, len(groups)):
            if groups[i] == [0, 0, 0, 0]:
                groups[i] = [0]
            elif groups[i] == [0, 0, 0, 1]:
                groups[i] = [1]
            elif groups[i] == [0, 0, 1, 0]:
                groups[i] = [2]
            elif groups[i] == [0, 0, 1, 1]:
                groups[i] = [3]
            elif groups[i] == [0, 1, 0, 0]:
                groups[i] = [4]
            elif groups[i] == [0, 1, 0, 1]:
                groups[i] = [5]
            elif groups[i] == [0, 1, 1, 0]:
                groups[i] = [6]
            elif groups[i] == [0, 1, 1, 1]:
                groups[i] = [7]
            elif groups[i] == [1, 0, 0, 0]:
                groups[i] = [8]
            elif groups[i] == [1, 0, 0, 1]:
                groups[i] = [9]
            elif groups[i] == [1, 0, 1, 0]:
                groups[i] = [10]
            elif groups[i] == [1, 0, 1, 1]:
                groups[i] = [11]
            elif groups[i] == [1, 1, 0, 0]:
                groups[i] = [12]
            elif groups[i] == [1, 1, 0, 1]:
                groups[i] = [13]
            elif groups[i] == [1, 1, 1, 0]:
                groups[i] = [14]
            elif groups[i] == [1, 1, 1, 1]:
                groups[i] = [15]
    return groups

def fromPowerTo2(groups, power):
    '''
    Transformă fiecare număr într-un grupuleț,
    corespunzător tabelelor de conversie rapidă
    din baza 2 la puterea *power* în baza 2
    :param groups: list of lists
    :param power: integer
    :return: list of lists
    '''
    if power == 2:
        for i in range(0, len(groups)):
            if groups[i] == [0]:
                groups[i] = [0, 0]
            elif groups[i] == [1]:
                groups[i] = [0, 1]
            elif groups[i] == [2]:
                groups[i] = [1, 0]
            elif groups[i] == [3]:
                groups[i] = [1, 1]
    elif power == 3:
        for i in range(0, len(groups)):
            if groups[i] == [0]:
                groups[i] = [0, 0, 0]
            elif groups[i] == [1]:
                groups[i] = [0, 0, 1]
            elif groups[i] == [2]:
                groups[i] = [0, 1, 0]
            elif groups[i] == [3]:
                groups[i] = [0, 1, 1]
            elif groups[i] == [4]:
                groups[i] = [1, 0, 0]
            elif groups[i] == [5]:
                groups[i] = [1, 0, 1]
            elif groups[i] == [6]:
                groups[i] = [1, 1, 0]
            elif groups[i] == [7]:
                groups[i] = [1, 1, 1]
    elif power == 4:
        for i in range(0, len(groups)):
            if groups[i] == [0]:
                groups[i] = [0, 0, 0, 0]
            elif groups[i] == [1]:
                groups[i] = [0, 0, 0, 1]
            elif groups[i] == [2]:
                groups[i] = [0, 0, 1, 0]
            elif groups[i] == [3]:
                groups[i] = [0, 0, 1, 1]
            elif groups[i] == [4]:
                groups[i] = [0, 1, 0, 0]
            elif groups[i] == [5]:
                groups[i] = [0, 1, 0, 1]
            elif groups[i] == [6]:
                groups[i] = [0, 1, 1, 0]
            elif groups[i] == [7]:
                groups[i] = [0, 1, 1, 1]
            elif groups[i] == [8]:
                groups[i] = [1, 0, 0, 0]
            elif groups[i] == [9]:
                groups[i] = [1, 0, 0, 1]
            elif groups[i] == [10]:
                groups[i] = [1, 0, 1, 0]
            elif groups[i] == [11]:
                groups[i] = [1, 0, 1, 1]
            elif groups[i] == [12]:
                groups[i] = [1, 1, 0, 0]
            elif groups[i] == [13]:
                groups[i] = [1, 1, 0, 1]
            elif groups[i] == [14]:
                groups[i] = [1, 1, 1, 0]
            elif groups[i] == [15]:
                groups[i] = [1, 1, 1, 1]
    return groups


def groupsToList(groups):
    '''
    Transformă o listă de grupulețe într-o listă normală
    :param groups: list of lists
    :return: list
    '''
    answer = []
    for i in groups:
        for j in i:
            answer.append(j)
    return answer


def test_makeGroups():
    assert (makeGroups([0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1], 2) ==
            [[0, 1], [1, 0], [1, 0], [1, 0], [1, 1], [1, 0], [1, 1], [0, 1], [0, 1]])
    assert (makeGroups([0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1], 3) ==
            [[0, 1, 1], [0, 1, 0], [1, 0, 1], [1, 1, 0], [1, 1, 0], [1, 0, 1]])
    assert (makeGroups([0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1], 4) ==
            [[0, 0, 0, 1], [1, 0, 1, 0], [1, 0, 1, 1], [1, 0, 1, 1], [0, 1, 0, 1]])
    assert (makeGroups([5, 13, 15, 10, 4, 3], 1) == [[5], [13], [15], [10], [4], [3]])

def test_showGroups():
    assert (showGroups([[0, 1], [1, 0], [1, 0], [1, 0], [1, 1], [1, 0], [1, 1], [0, 1], [0, 1]]) ==
            '|01|10|10|10|11|10|11|01|01|')
    assert (showGroups([[0, 1, 1], [0, 1, 0], [1, 0, 1], [1, 1, 0], [1, 1, 0], [1, 0, 1]]) ==
            '|011|010|101|110|110|101|')
    assert (showGroups([[0, 0, 0, 1], [1, 0, 1, 0], [1, 0, 1, 1], [1, 0, 1, 1], [0, 1, 0, 1]]) ==
            '|0001|1010|1011|1011|0101|')
    assert (showGroups([[5], [13], [15], [10], [4], [3]]) == '|5|D|F|A|4|3|')

def test_from2toPower():
    assert (from2toPower([[0, 1], [1, 0], [1, 0], [1, 0], [1, 1], [1, 0], [1, 1], [0, 1], [0, 0]], 2) ==
            [[1], [2], [2], [2], [3], [2], [3], [1], [0]])
    assert (from2toPower([[0, 1, 1], [0, 1, 0], [1, 0, 1], [1, 1, 0], [1, 1, 0], [1, 0, 1]], 3) ==
            [[3], [2], [5], [6], [6], [5]])
    assert (from2toPower([[0, 0, 0, 1], [1, 0, 1, 0], [1, 0, 1, 1], [1, 0, 1, 1], [0, 1, 0, 1]], 4) ==
            [[1], [10], [11], [11], [5]])

def test_fromPowerTo2():
    assert (fromPowerTo2([[1], [2], [2], [2], [3], [2], [3], [1], [0]], 2) ==
            [[0, 1], [1, 0], [1, 0], [1, 0], [1, 1], [1, 0], [1, 1], [0, 1], [0, 0]])
    assert (fromPowerTo2([[3], [2], [5], [6], [6], [5]], 3) ==
            [[0, 1, 1], [0, 1, 0], [1, 0, 1], [1, 1, 0], [1, 1, 0], [1, 0, 1]])
    assert (fromPowerTo2([[1], [10], [11], [11], [5]], 4) ==
            [[0, 0, 0, 1], [1, 0, 1, 0], [1, 0, 1, 1], [1, 0, 1, 1], [0, 1, 0, 1]])
    assert (fromPowerTo2([[5], [13], [15], [10], [4], [3]], 4) ==
            [[0, 1, 0, 1], [1, 1, 0, 1], [1, 1, 1, 1], [1, 0, 1, 0], [0, 1, 0, 0], [0, 0, 1, 1]])

def test_groupsToList():
    assert (groupsToList([[0, 1, 1], [0, 1, 0], [1, 0, 1], [1, 1, 0], [1, 1, 0], [1, 0, 1]]) ==
            [0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1])
    assert (groupsToList([[5], [13], [15], [10], [4], [3]]) == [5, 13, 15, 10, 4, 3])
