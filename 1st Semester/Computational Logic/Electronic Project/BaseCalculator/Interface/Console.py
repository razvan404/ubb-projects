from Domain.Converts import silentConvertUsingSubstitution, silentConvertUsingSuccesiveDivisions, silentConvert
from Domain.Fast_Converts import makeGroups, showGroups, groupsToList, from2toPower, fromPowerTo2
from Domain.Number import numberToList, listToNumber, compare
from Domain.Operations import add, multiply, divide, decrease
from Interface.Menu import globalMenu, convertMenu, invalid, arithMenu, quick1Menu, quick2Menu, quickMenu, contMenu
import os

class Console():

    def __convertUsingSuccesiveDivisions(self):
        print()
        print("!) Baza din care convertești numărul trebuie să fie mai mare decât baza în care dorești să fie"
              " convertit numărul!")
        x = input(' Introdu numărul care dorești să fie convertit: ')
        oldBase = int(input(' Introdu baza din care dorești să fie convertit numărul: '))
        if oldBase > 16 or oldBase < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16 și mai mare sau egal cu 2')
        newBase = int(input(' Introdu baza in care dorești sa fie convertit numărul: '))
        if newBase > 16 or newBase < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16 și mai mare sau egal cu 2')
        if newBase >= oldBase:
            raise ValueError(
                'Pentru a efectua operația de împărțiri succesive, noua bază trebuie să fie '
                'mai mică decât vechea bază')
        print()
        x = numberToList(x, oldBase)
        print('Algoritm conversie prin împărțiri succesive. Acesta constă in 2 pași:')
        print('   Pasul 1. Împărțim repetat numărul introdu la noua baza, operația fiind ralizată in vechea bază')
        result = []
        while listToNumber(x) != '0':
            cat = divide(x, newBase, oldBase)[0]
            rest = divide(x, newBase, oldBase)[1]
            if listToNumber(cat) != '0':
                print('     Împărțim pe', listToNumber(x), 'la', newBase, 'în baza', oldBase, '| Obținem câtul',
                      listToNumber(cat), 'si restul', rest)
            else:
                print('     Împărțim pe', listToNumber(x), 'la', newBase, 'în baza', oldBase, '| Obținem restul',
                      rest)
            x = cat
            result.append(rest)
        print('   Pasul 2. Luăm resturile în ordine inversă pentru a oține rezultatul')
        result.reverse()
        print('Numărul introdus va avea valoarea', listToNumber(result), 'în baza', newBase)

    def __convertUsingSubstitution(self):
        print()
        print("!) Baza din care convertești numărul trebuie să fie mai mică decât baza în care dorești să fie"
              " convertit numărul!")
        x = input(' Introdu numărul care dorești să fie convertit: ')
        oldBase = int(input(' Introdu baza din care dorești sa fie convertit numărul: '))
        if oldBase > 16 or oldBase < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16 și mai mare sau egal cu 2')
        newBase = int(input(' Introdu baza in care dorești sa fie convertit numărul: '))
        if newBase > 16 or newBase < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16 și mai mare sau egal cu 2')
        if newBase <= oldBase:
            raise ValueError(
                'Pentru a efectua operația de substituție, noua bază trebuie să fie '
                'mai mare decât vechea bază')
        print()
        x = numberToList(x, oldBase)
        result = []
        p = [1]
        print('Algoritm conversie prin substituție. Înmulțim fiecare cifră cu vechea bază la puterea corespondentă și '
              'adunăm fiecare rezultat obținut')
        print('   !) Toate operațiile vor fi realizate în noua bază')
        for i in range(len(x) - 1, -1, -1):
            a = multiply(p, x[i], newBase)
            result = add(result, a, newBase)
            text = '     Înmultim cifra ' + str(x[i]) + ' cu ' + str(listToNumber(p)) + ' (' + str(oldBase) + \
                  ' la puterea ' + str(len(x) - i - 1) + ' în baza ' + str(newBase) + '). Vom obține ' + \
                  str(listToNumber(a)) + ' și îl adăugăm la rezultatul final, adică acesta va deveni ' + \
                  str(listToNumber(result))
            print(text)
            p = multiply(p, oldBase, newBase)
        print('Numărul introdus va avea valoarea', listToNumber(result), 'in baza', newBase)

    def __convertUsingCustomBase(self):
        print()
        x = input(' Introdu numărul care dorești să fie convertit: ')
        oldBase = int(input(' Introdu baza din care dorești sa fie convertit numărul: '))
        if oldBase > 16 or oldBase < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16 și mai mare sau egal cu 2')
        newBase = int(input(' Introdu baza in care dorești sa fie convertit numărul: '))
        if newBase > 16 or newBase < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16 și mai mare sau egal cu 2')
        if oldBase == newBase:
            raise ValueError(
                'Bazele trebuie să fie diferite.')
        x = numberToList(x, oldBase)
        if oldBase > 10:
            print()
            print('   Pasul 1. Vom converti numărul', listToNumber(x), 'din baza', oldBase, 'în baza 10 prin împărțiri'
                  ' succesive deoarece', oldBase, 'este mai mare decât 10')
            r = silentConvertUsingSuccesiveDivisions(x, oldBase, 10)
            text = '    În urma operației de conversie prin împărțiri succesive, numărul ' + str(
                listToNumber(x)) + ' va deveni ' \
                   + str(listToNumber(r)) + ' în baza 10'
            print(text)
        else:
            print()
            print('   Pasul 1. Vom converti numărul', listToNumber(x), 'din baza', oldBase, 'în baza 10 prin '
                  'substituție succesive deoarece', oldBase, 'este mai mic decât 10')
            r = silentConvertUsingSubstitution(x, oldBase, 10)
            text = '    În urma operației de conversie prin substituție, numărul ' + str(listToNumber(x)) + ' va ' \
                   'deveni ' + str(listToNumber(r)) + ' în baza 10'
            print(text)
        if 10 > newBase:
            print()
            print('   Pasul 2. Vom converti numărul', listToNumber(r), 'din baza 10 în baza', newBase, 'prin împărțiri'
                                                                                            ' succesive deoarece',
                  newBase, 'este mai mic decât 10')
            ans = silentConvertUsingSuccesiveDivisions(r, 10, newBase)
            text = '    În urma operației de conversie prin împărțiri succesive, numărul ' + str(listToNumber(r)) + \
                   ' va deveni ' + str(listToNumber(ans)) + ' în baza ' + str(newBase)
            print(text)
        else:
            print()
            print('   Pasul 2. Vom converti numărul', listToNumber(r), 'din baza 10 în baza', newBase, ' prin '
                                                                                            'substituție deoarece',
                  newBase, 'este mai mare decât 10')
            ans = silentConvertUsingSubstitution(r, 10, newBase)
            text = '    În urma operației de conversie prin substituție, numărul ' + str(listToNumber(r)) + \
                   ' va deveni ' + str(listToNumber(ans)) + ' în baza ' + str(newBase)
            print(text)

    def __fastBaseFrom2(self, option):
        if option != '1' and option != '2' and option != '3':
            print(invalid())
        else:
            print()
            option = int(option) + 1
            x = input(' Introdu numărul care dorești să fie convertit: ')
            x = numberToList(x, 2)
            while len(x) % option != 0:
                x.insert(0, 0)
            print('Algoritm de convertire rapidă din baza 2 în baza', pow(2, option))
            print('   Pasul 1. Împărțim numărul în grupulețe de câte', option)
            groups = makeGroups(x, option)
            print('Vom obține', showGroups(groups))
            print('   Pasul 2. Înlocuim grupulețele cu corespondentele lor din tabelul de convertire rapidă')
            groups = from2toPower(groups, option)
            print('Vom obține', showGroups(groups))
            print('   În final, numărul obținut va fi', listToNumber(groupsToList(groups)), 'în baza', pow(2, option))

    def __fastBaseTo2(self, option):
        if option != '1' and option != '2' and option != '3':
            print(invalid())
        else:
            option = int(option) + 1
            print()
            x = input(' Introdu numărul care dorești să fie convertit: ')
            x = numberToList(x, pow(2, option))
            print('Algoritm de convertire rapidă în baza 2 din baza', pow(2, option))
            print('   Pasul 1. Împărțim numărul în grupulețe de câte 1')
            groups = makeGroups(x, 1)
            print('Vom obține', showGroups(groups))
            print('   Pasul 2. Înlocuim grupulețele cu corespondentele lor din tabelul de convertire rapidă')
            groups = fromPowerTo2(groups, option)
            print('Vom obține', showGroups(groups))
            print('   În final, numărul obținut va fi', listToNumber(groupsToList(groups)), 'în baza 2')

    def __sum(self):
        print()
        x = input('Introdu valoarea primului număr: ')
        base1 = int(input('Introdu baza primului număr: '))
        if base1 > 16 or base1 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        x = numberToList(x, base1)
        y = input('Introdu valoarea celui de-al doilea număr: ')
        base2 = int(input('Introdu baza celui de-al doilea număr: '))
        if base2 > 16 or base2 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        y = numberToList(y, base2)
        base3 = int(input('Introdu baza în care dorești sa fie efectuata operația: '))
        if base3 > 16 or base3 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        x = silentConvert(x, base1, base3)
        y = silentConvert(y, base2, base3)
        print('Primul număr va fi', listToNumber(x), 'în baza nouă, iar al doilea va fi', listToNumber(y))
        print()
        sum = add(x, y, base3)
        row1 = '     '
        row2 = '     '
        row3 = '     '
        row4 = '     '
        n = len(sum)
        for i in range(0, n - len(x)):
            row1 += ' '
        row1 += str(listToNumber(x)) + '(' + str(base3) + ')+'
        for i in range(0, n - len(y)):
            row2 += ' '
        row2 += str(listToNumber(y)) + '(' + str(base3) + ')'
        for i in range(0, n + 4):
            row3 += '='
        for i in range(0, n - len(sum)):
            row4 += ' '
        row4 += str(listToNumber(sum)) + '(' + str(base3) + ')'
        operation = row1 + '\n' + row2 + '\n' + row3 + '\n' + row4 + '\n'
        print(operation)
        print('Suma celor doua numere este', listToNumber(sum), 'în baza', base3)

    def __difference(self):
        print()
        print("!) Primul număr trebuie să fie mai mare decât al doilea!")
        x = input('Introdu valoarea primului număr: ')
        base1 = int(input('Introdu baza primului număr: '))
        if base1 > 16 or base1 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        x = numberToList(x, base1)
        y = input('Introdu valoarea celui de-al doilea număr: ')
        base2 = int(input('Introdu baza celui de-al doilea număr: '))
        if base2 > 16 or base2 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        y = numberToList(y, base2)
        base3 = int(input('Introdu baza în care dorești sa fie efectuata operația: '))
        if base3 > 16 or base3 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        x = silentConvert(x, base1, base3)
        y = silentConvert(y, base2, base3)
        print('Primul număr va fi', listToNumber(x), 'în baza nouă, iar al doilea va fi', listToNumber(y))
        if compare(x, y) == -1:
            raise ValueError('Primul număr trebuie să fie mai mare decat al doilea')
        print()
        row1 = '     '
        row2 = '     '
        row3 = '     '
        row4 = '     '
        n = len(x)
        row1 += str(listToNumber(x)) + '(' + str(base3) + ')-'
        for i in range(0, n - len(y)):
            row2 += ' '
        row2 += str(listToNumber(y)) + '(' + str(base3) + ')'
        for i in range(0, n + 4):
            row3 += '='
        dif = decrease(x, y, base3)
        for i in range(0, n - len(dif)):
            row4 += ' '
        row4 += str(listToNumber(dif)) + '(' + str(base3) + ')'
        operation = row1 + '\n' + row2 + '\n' + row3 + '\n' + row4 + '\n'
        print(operation)
        print('Diferenta celor doua numere este', listToNumber(dif), 'în baza', base3)

    def __product(self):
        print()
        x = input('Introdu valoarea primului număr: ')
        base1 = int(input('Introdu baza primului număr: '))
        if base1 > 16 or base1 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        x = numberToList(x, base1)
        y = input('Introdu cifra cu care dorești sa fie înmulțit: ')
        base2 = int(input('Introdu baza cifrei cu care dorești sa fie înmulțit: '))
        if base2 > 16 or base2 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        y = numberToList(y, base2)
        base3 = int(input('Introdu baza în care dorești să fie efectuata operația: '))
        if base3 > 16 or base3 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        x = silentConvert(x, base1, base3)
        y = silentConvert(y, base2, base3)
        print('Primul număr va fi', listToNumber(x), 'în baza nouă, iar al doilea va fi', listToNumber(y))
        y = int(listToNumber(y))
        if y > 9 or y < 0:
            raise ValueError(
                'Numărul introdus nu este o cifra în baza in care dorești să fie efectuata operația')
        print()
        mul = multiply(x, y, base3)
        row1 = '     '
        row2 = '     '
        row3 = '     '
        row4 = '     '
        n = len(mul)
        for i in range(0, n - len(x)):
            row1 += ' '
        row1 += str(listToNumber(x)) + '(' + str(base3) + ')*'
        for i in range(0, n - 1):
            row2 += ' '
        row2 += str(y) + '(' + str(base3) + ')'
        for i in range(0, n + 4):
            row3 += '='

        for i in range(0, n - len(mul)):
            row4 += ' '
        row4 += str(listToNumber(mul)) + '(' + str(base3) + ')'
        operation = row1 + '\n' + row2 + '\n' + row3 + '\n' + row4 + '\n'
        print(operation)
        print('Produsul celor doua numere este', listToNumber(mul), 'în baza', base3)

    def __division(self):
        print()
        x = input('Introdu valoarea primului număr: ')
        oldBase = int(input('Introdu baza primului număr: '))
        if oldBase > 16 or oldBase < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        x = numberToList(x, oldBase)
        y = input('Introdu cifra pe care vrei sa o imparti la primul număr: ')
        newBase = int(input('Introdu baza cifrei pe care vrei sa o imparti la primul număr: '))
        if newBase > 16 or newBase < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        y = numberToList(y, newBase)
        base3 = int(input('Introdu baza în care dorești sa fie efectuata operația: '))
        if base3 > 16 or base3 < 2:
            raise ValueError(
                'Baza este invalidă, trebuie să fie un număr natural nenul mai mic sau egal '
                'cu 16')
        x = silentConvert(x, oldBase, base3)
        y = silentConvert(y, newBase, base3)
        print('Primul număr va fi', listToNumber(x), 'în baza nouă, iar al doilea va fi', listToNumber(y), 'în baza nouă')
        if len(y) > 1:
            raise ValueError(
                'Numărul introdus nu este o cifră în baza în care dorești să fie efectuată operația')
        y = int(y[0])
        if y == 0:
            raise ValueError(
                'Nu se poate împărți un număr la 0')
        print()
        cat = divide(x, y, base3)[0]
        rest = divide(x, y, base3)[1]
        y = listToNumber([y])
        row1 = '     '
        row2 = '     '
        row3 = '     '
        row4 = '     '
        n = len(x)
        row1 += str(listToNumber(x)) + '(' + str(base3) + '):'
        for i in range(0, n - 1):
            row2 += ' '
        row2 += str(y) + '(' + str(base3) + ')'
        for i in range(0, n + 4):
            row3 += '='
        for i in range(0, n - len(cat)):
            row4 += ' '
        row4 += str(listToNumber(cat)) + '(' + str(base3) + ')' + ' rest ' + str(listToNumber([rest])) + \
                '(' + str(base3) + ')'
        operation = row1 + '\n' + row2 + '\n' + row3 + '\n' + row4 + '\n'
        print(operation)
        print('Împărtirea celor doua numere are ca rezultat câtul',
              listToNumber(cat),
              'și restul', listToNumber([rest]), 'în baza', base3)

    def begin(self):
        clear = lambda: os.system('cls')
        while True:
            option = input(globalMenu())
            if option == '1':
                clear()
                option = input(convertMenu())
                if option == '1':
                    clear()
                    try:
                        self.__convertUsingSuccesiveDivisions()
                    except ValueError as ve:
                        print(ve)
                elif option == '2':
                    clear()
                    try:
                        self.__convertUsingSubstitution()
                    except ValueError as ve:
                        print(ve)
                elif option == '3':
                    clear()
                    try:
                        self.__convertUsingCustomBase()
                    except ValueError as ve:
                        print(ve)
                else:
                    invalid()
            elif option == '2':
                clear()
                option = input(quickMenu())
                if option == '1':
                    clear()
                    option = input(quick1Menu())
                    clear()
                    try:
                        self.__fastBaseFrom2(option)
                    except ValueError as ve:
                        print(ve)
                elif option == '2':
                    clear()
                    option = input(quick2Menu())
                    clear()
                    try:
                        self.__fastBaseTo2(option)
                    except ValueError as ve:
                        print(ve)
                else:
                    invalid()
            elif option == '3':
                clear()
                option = input(arithMenu())
                if option == '1':
                    clear()
                    try:
                        self.__sum()
                    except ValueError as ve:
                        print(ve)
                elif option == '2':
                    clear()
                    try:
                        self.__difference()
                    except ValueError as ve:
                        print(ve)
                elif option == '3':
                    clear()
                    try:
                        self.__product()
                    except ValueError as ve:
                        print(ve)
                elif option == '4':
                    clear()
                    try:
                        self.__division()
                    except ValueError as ve:
                        print(ve)
                else:
                    invalid()
            else:
                invalid()

            option = input(contMenu())
            if option == '0':
                print("\nLa revedere!")
                break
            else:
                clear()
                
        