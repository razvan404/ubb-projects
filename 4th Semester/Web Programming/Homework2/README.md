# <b>Tema 2 - CSS</b>
Problemele de mai jos vor fi rezolvate folosind pentru pozitionare in special tag-urile div, span, ul, li si stiluri CSS. Nu se vor folosi tabele pentru pozitionare, framework-uri CSS sau JavaScript. Rezolvarea problemelor va fi testata pe Microsoft Edge, Firefox, Google Chrome si Opera, la rezolutii full screen (ferestre maximizate) si rezolutii inferioare rezolutiei maxime a ecranului.

Notare:

- primele doua probleme pentru maxim nota 5;
- primele patru probleme pentru maxim nota 7;
- primele cinci probleme pentru maxim nota 8;
- primele sase probleme pentru maxim nota 9;
- toate pentru maxim nota 10.

Studentul va preda cel putin o problema la alegerea cadrului didactic, dar va stii sa raspunda la intrebari legate de rezolvarile tuturor problemelor prezentate (si din teoria aferenta).

<ol>
<li>
Un div parinte (chenarul negru) va contine doua divuri interioare, unul in stanga si unul in dreapta. Cele doua div-uri interioare au fiecare latimea fixa de 200 de pixeli. Div-ul interior din stanga contine text centrat orizontal, iar div-ul interior din dreapta contine o imagine cu latimea cel mult 200 de pixeli, centrata si ea orizontal daca latimea sa este mai mica de 200 de pixeli. Cele doua div-uri interioare vor avea aceasi inaltime (in functie de continutul lor), aceasta fiind evident si inaltimea div-ului parinte. Daca inaltimea div-ului interior din dreapta (cel cu imaginea) este mai mare decat inaltimea div-ului interior din stanga (cel cu textul) – datorita faptului ca inaltimea imaginii din dreapta este mai mare decat inaltimea pe care o ocupa textul – in div-ul interior din stanga text-ul va fi centrat si pe verticala. Daca inaltimea div-ului interior din stanga este mai mare decat inaltimea div-ului interior din dreapta – datorita faptului ca inaltimea ocupata de text este mai mare decat inaltimea imaginii – in div-ul interior din dreapta imaginea va fi centratata si pe verticala. Se pot folosi mai multe div-uri imbricate daca este cazul. Codul CSS/HTML trebuie sa se comporte corespunzator cerintelor de mai sus la schimbarea continutului (text, respectiv imagine). Se vor testa toate combinatiile posibile (text mai inalt, imagine mai inalta, imagine mai ingusta, etc). Important: inaltimea nu se fixeaza (se presupune ca este necunoscuta).

Exemplu:

<img src="https://i.imgur.com/OQRNhan.png">
</li>
<li>
Sa se descrie folosind cod HTML structura unui site ce contine: un header, un meniu (lista de elemente), o div principal cu continut si un footer. Structura site-ului va fi apoi stilizata folosind cel putin doua fisere CSS externe (referite pe rand in antetul paginii). Pentru unul din fisierele CSS meniul va fi orizontal, iar pentru celalalt vertical. Singurul lucrul permis a se modifica intre cele doua variante de vizualizare a site-ului este numele fisierului CSS la care se face referire in antetul paginii. Nu se vor face modificari la structura documentului.

<img src="https://i.imgur.com/1LWT1ZR.png"><img src="https://i.imgur.com/V9wjgwJ.png">
</li>
<li>
Un site contine un header (rosu), un meniu orizontal sau vertical (galben), o zona principala cu continut (verde) si un footer (roz). Se cere:

- Site-ul va fi stilizat folosind CSS;
- Header-ul va avea o inaltime fixa de 100 de pixeli;
- Meniul va avea o intaltime de 25px si va fi redat printr-o lista, acesta putand fi fie orizontal (vezi figurile de mai jos), fie vertical in stanga div-ului principal;
- Footer-ul va avea o inaltime fixa de 60 de pixeli;
- Div-ul principal (de culoare verde, avand continutul Main View in exemplu) va ocupa toata latimea ferestrei si toata inaltimea disponibila a acesteia (dupa ce se scade inaltimea header-ului, a footer-ului si a meniului). Daca este cazul, acest div poate avea o inaltime care sa se adapteze la continut, mai mare ca inaltimea ferestrei browserului (vezi figura de mai jos), caz in care browserul va afisa bara de scroll verticala din partea dreapta. Daca acest div are continut minim, div-ul ce reprezinta footer-ul se va regasi intotdeauna in partea de jos a ferestrei (footerul nu are voie sa “urce” mai sus de marginea de jos a ferestrei browserului, daca textul din div-ul verde e putin, poate cel mult sa fie “impins” in jos de mult continut in div-ul verde). De asemenea, footerul poate fi “impins” in jos de un posibil meniu vertical cu multe elemente. Geometria site-ului se va pastra la redimensionarea ferestrei browser-ului;
- Daca utilizatorul ingusteaza latimea ferestrei browserului pana la o latime minima, geometria site-ului se va pastra, footerul fiind “impins” in jos la nevoie, afisandu-se si un scroll bar vertical.

<img src="https://i.imgur.com/tijzjAE.png"><img src="https://i.imgur.com/APsiUTk.png">
</li>
<li>
Folosind sprite-uri CSS, pe baza imaginii de mai jos, sa se creeze un meniu de socializare vertical cu iconitele initial disabled. La mouse over peste una dintre iconitele de socializare, aceasta va deveni din disabled enabled (sa va colora). Fiecare iconita se va afisa initial doar disabled, fiind afisata colorat doar la mouse over. Nu se va folosi JavaScript. Se va folosi fix imaginea de mai jos, aceasta nu se va decupa. Pe baza unor modificari minimale in codul CSS meniul de socializare vertical se va transforma intr-unul orizontal.

<img src="https://i.imgur.com/eJvKNL6.png">
</li>
<li>
O pagina HTML va contine o lista de imagini. Sa se stilizeze aceasta lista cu doua stiluri diferite pentru a obtine un effect vizual cat mai asemnator exemplelor de mai jos. Singurul lucrul permis a se modifica intre cele doua variante de vizualizare a listei de imagini este numele fisierului CSS la care se face referire in antetul paginii. NU se vor face modificari la structura documentului, ambele rezolvari trebuie sa contina fix acelasi cod HTML.

<img src="https://i.imgur.com/42i9vZD.png"><img src="https://i.imgur.com/PreFRxh.png">
</li>
<li>
Stilizati mai multe input-uri de tip text astfel incat completarea acestora sa se faca asemanator figurii de mai jos. Input-urile vor accepta un caracter per “patratica”. Nu este permisa folosirea mai multor input-uri pentru acelasi camp (pentru nume spre exemplu). Atributele CSS folosite (width, font-family, font-size, etc) se vor combina/corespunzator cu atributele HTML (maxlength) pentru un efect corespunzator. Nu se vor accepta mai multe caractere in input decat se pot introduce “vizual”.

<img src="https://i.imgur.com/7aWoOVi.png">
</li>
<li>
Se da urmatorul cod HTML:

```
<ul class="dialog">
 	<li class="alice">Lorem ipsum dolor sit amet, consectetur adipisicing elit</li>
 	<li class="bob">Sed ut perspiciatis unde omnis iste nat us error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt</li>
 	<li class="alice">Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse</li>
</ul>
```

Sa se stilizeze acest cod HTML folosind clasele CSS dialog, alice si bob pentru a se obtine un efect vizual ca in figura de mai jos:

<img src="https://i.imgur.com/vke8BiQ.png">

Observatii:
- Lista va putea contine mai mult de trei elemente plasate in clasele alice, bob (eventual si alte “personaje”);
- Colturile ferestrei de dialog vor fi rotunjite;
- Fereastra de dialog pentru fiecare personaj va avea o latime si o intaltime minima, valori ce se vor adapta in functie de dimensiunea textului spus de fiecare personaj si de dimensiunile ferestrei browserului;
- Textul din cadrul ferestrei de dialog va fi centrat pe orizontala;
- Daca textul din cadrul unui element al listei este foarte lung, fereastra de dialog “rostita” de alice sau bob se va redimensiona pe latime daca fereastra browserului permite si apoi pe inaltime, pastrand insa constante proportiile colturilor (nu se va redimensiona fereastra de dialog fara pastrarea proportiilor acesteia);
- Avatarele lui alice si bob vor fi incarcate dintr-un sprite (a se vedea problema 4).

</li>
</ol>