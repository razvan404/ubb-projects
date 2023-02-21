#6.  a. Sa se determine daca lista are numar par de elemente, fara sa se calculeze lungimea.
#    b. Sa se stearga toate aparitiile unui element e dintr-o lista.class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None
    
class Lista:
    def __init__(self):
        self.prim = None

'''
crearea unei liste din valori citite pana la 0
'''
def creareLista():
    lista = Lista()
    lista.prim = creareListaRec()
    return lista

def creareListaRec():
    x = int(input("Introdu urmatorul element introdus: "))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareListaRec()
        return nod
    
'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tiparRec(lista.prim)
    print()
    
def tiparRec(nod):
    if nod != None:
        print(nod.e, end=' ')
        tiparRec(nod.urm)
        

'''
rezolvare exercitiu
'''

def sublista(lista):
    rtrn = Lista()
    rtrn.prim = lista.prim.urm
    return rtrn

def adaugaPrim(lista, e):
    nod = Nod(e)
    nod.urm = lista.prim
    lista.prim = nod
    return lista

def numarParRec(lista):
    if lista.prim == None:
        return True
    return not numarParRec(sublista(lista))

def stergeElementRec(lista, e):
    if lista.prim == None:
        return Lista()
    elif lista.prim.e == e:
        return stergeElementRec(sublista(lista), e)
    else:
        return adaugaPrim(stergeElementRec(sublista(lista), e), lista.prim.e)
'''
program pentru test
'''
        
def main():
    print("Se vor citi elemente intr-o lista pana la intalnirea lui 0.")
    list = creareLista()
    print("Valoarea de adevar a propozitiei 'Lista data are un numar par de elemente': ", numarParRec(list))
    e = int(input("Elementul care va fi eliminat din lista introdusa anterior: "))
    print("Lista fara elementul introdus: ")
    l_sters = stergeElementRec(list, e)
    tipar(l_sters)
main() 
