# <b>Metode Avansate de Programare, 2022 – 2023, LABORATOR 1</b>

<h2>Obiective:</h2>

- instalarea mediilor de dezvoltare necesare pentru a scrie programare
    folosind limbajul Java
- familiariarea cu sintaxa limbajului Java

Obs. Acest laborator nu intra in calculul notei de la laborator, dar sunteti
incurajati sa realizati cerintele de mai jos.

```
A. Instalați un mediu de dezvoltare intregrat pt Java (Java IDE ) pe laptopurile proprii și încercați
să vă familiarizați cu acesta.
La curs si seminar vom folosi: InteliJ IDEA, Ultimate Edition (Pentru a putea activa licenta,
creati un JetBrains Account cu adresa de mail de la facultate).
```
[Download JDK]
https://www.oracle.com/java/technologies/downloads/


[Download InteliJ IDEA]
https://account.jetbrains.com/login

```
B. Se citesc, ca parametri în linia de comanda, separati prin spatiu, mai multe numere complexe
de forma a+b*i și o operație, sub forma unui operator (+, - , *, /).


1) Sa se verifice dacă parametri citiți în linia de comanda, separați prin spațiu, reprezintă o
expresie aritmetica de forma: 𝑛1 𝑜𝑝 𝑛2 𝑜𝑝 ...𝑜𝑝 𝑛𝑘, unde 𝑛1 , 𝑛2 ... 𝑛𝑘 sunt numere complexe
de forma 𝑎+𝑏∗𝑖, iar 𝑜𝑝 este operatorul dat.
 Exemplu: 2+3∗𝑖 + 5−6∗𝑖 + −2+𝑖
   args[0]= 2+3∗𝑖
   args[1]= +
   args[2]= 5−6∗𝑖
   args[3]= +
   args[4]= −2+𝑖

2) Dacă parametri citiți în linia de comandă reprezintă o expresie aritmetică de forma
descrisă la punctul 1, se cere sa se afișeze rezultatul acestei expresii.
 Exemplu: pentru expresia data se va afisa: 5−2∗𝑖
```
<h2>Observatii:</h2>

Sunteti incurajati sa veniti cu propria proiectare pentru rezolvarea problemei
daca aceasta este corecta si respecta principiile de proiectare orientata obiect
invatate pana acum (Vezi SOLID design principles). O proiectare simplista
(totul intr-un fisier, fara clase specializate ....) care doar rezolva problema va fi
punctata cu nota 8.

**Sugestii de proiectare** (daca nu va este teama sa va jucati cu clasele, puteti veni
si cu propria abstractizare, chiar sunteti incurajati).
Se vor defini clasele:

- **NumarComplex**, având ca atribute re, im de tip real, iar ca metode operatiile
    definite pe multimea numerelor complexe: adunare, scadere, inmultire,
    impartire si conjugatul.
- **ComplexExpression**, clasa abstracta, ce are ca atribute operation de tipul
    **Operation** (enum având patru valori posibile: **_ADDITION_** , **_SUBSTRACTION_** ,
    **_MULTIPLICATION_** , **_DIVISION_** ) si un vector (array) args de numere complexe, iar
    ca metode, o metodă execute ce returneaza rezultatul expresiei aritmetice,
    apeland pentru aceasta metoda abstractă **executeOneOperation**
    [TemplateMethodDesignPattern]. Derivati din clasa ComplexExpression
    clasele necesare pentru executia celor patru tipuri de expresii, definite la punctul
    B.l., suprascriind, corespunzator tipului operatiei dat (+,-,/,*), metoda
    executeOneOperation - executa o operatie din insiruirea de operatii ale
    expresiei.
- **ExpressionFactory** (singleton) [SingletonDesignPattern]
    [FactoryMethodDesignPattern] având metoda createExpression cu signatura:
    **public ComplexExpression createExpression(Operation operation, Complex[] args)**
    si care creează o expresie în funcție de valoarea parametrului operation (vezi
    diagrama de clase).
- **ExpressionParser** care parsează expresia, verifică dacă este validă si
    construiește, folosind un obiect de tipul ExpressionFactory, expresia
    corespunzatoare operatorului dat.


<h2>Alte Referinte:</h2>

[FactoryMethodDesignPattern] https://www.tutorialspoint.com/design_pattern/factory_pattern.htm

[SingletonDesignPattern] https://www.tutorialspoint.com/design_pattern/singleton_pattern.htm

[TemplateMethodDesignPattern] https://www.tutorialspoint.com/design_pattern/template_pattern.htm