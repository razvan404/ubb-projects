# <strong>Tema 4 - JavaScript</strong>

1. Sa se scrie o pagina HTML ce contine doua liste cu mai multe elemente fiecare, create cu ajutorul tagului &lt;select&gt;. La un dubluclick pe un element al primei liste, acesta va fi mutat in lista a doua si invers. Nu se vor folosi biblioteci de functii, jQuery, pluginuri, etc.
2. Un formular web va permite unui utilizator sa isi introduca numele, data nasterii, varsta si adresa de e-mail. La apasarea unui buton “Trimite” se vor valida toate aceste campuri daca sunt completate si daca sunt completate corect. Daca da, se va afisa un mesaj “Datele sunt completate corect”, altfel, se va afisa un mesaj de genul “Campurile nume si varsta nu sunt completate corect”, aceste campuri fiind “incercuite” intr-o bordura rosie. Toate aceste validari vor fi implementate pe client in JavaScript. Nu se vor folosi biblioteci de functii, jQuery, pluginuri, etc.
3. Sa se implementeze folosind JavaScript urmatoarea problema. O matrice cu numar par de elemente, reprezentata vizual sub forma unui tabel, contine perechi de numere initial ascunse. Daca utilizatorul da click pe doua celule ale tabelului ce contin numere egale acestea vor fi afisate si vor ramane afisate. Daca numerele continute in cele doua celule nu sunt egale, vor fi ascunse din nou dupa un numar de 2, 3 secunde. Jocul se termina cand toate perechile de numere au fost ghicite. Dupa prima implementare a jocului, se va crea o noua versiune in care numerele vor fi inlocuite cu imagini (ce contin fructe spre exemplu, sau “profi” de pe pagina facultatii). Problema mai este recunoscuta si sub numele de Memory Game. Nu se vor folosi biblioteci de functii, jQuery, pluginuri, etc.
4. Sa se scrie o pagina HTML ce contine un tabel cu cel putin trei coloane si cel putin trei linii. Prima coloana reprezinta antetul. Cand utilizatorul va da click pe o celula din antet, elementele din tabel se vor sorta crescator sau descrescator in functie de valorile prezente pe linia corespunzatoare antetului pe care s-a dat click. Codul JavaScript va fi reutilizabil si va permite crearea unui comportament de tabel sortabil pentru mai multe tabele existente in cadrul paginii. Nu se vor folosi biblioteci de functii, jQuery, pluginuri, etc. Exemplu de tabel ce se doreste a fi sortat (sortarea se va face alfabetic dupa numele fructului, dupa pret sau dupa cantitate):

        Fructe	    Mere	Pere
        Pret	    3	    4
        Cantitate	8	    6

    Dupa rezolvarea problemei, implementati o noua varianta in care capul de tabel este orizontal, nu vertical. Nu se vor folosi biblioteci de functii, jQuery, pluginuri, etc.

5. Intr-o pagina HTML exista o lista descrisa cu ajutorul tagului &lt;ol&gt;. Fiecare element din lista (&lt;li&gt;) contine o imagine (&lt;img&gt;), si un link (&lt;a&gt;). Elemente listei, mai putin primul dintre ele, nu sunt vizibile initial (se poate folosi in acest sens CSS). Afisarea unui element din lista presupune afisarea imaginii si a textului ca link peste imagine (a se vedea ca exemplu carouselul din pagina facultatii). Dupa n secunde printr-un efect de tranzitie va fi afisat urmatorul element din lista. Se vor implementa si doua butoane Next si Previous care vor permite afisarea elementelor urmatoare sau anterioare fara a se astepta trecerea celor n secunde. Nu se vor folosi biblioteci de functii, jQuery, pluginuri, etc.
6. O pagina HTML va contine un tabel cu n linii si n coloane. Celulele tabelului contin numere de la 1 la n2 intr-o ordine aleatoare. Una dintre celule este libera. Folosind JavaScript sa se creeze in cadrul paginii un joc de tip puzzle care la apasarea tastelor sageti va interschimba celula libera cu celula adiacenta (corespunzatoare tastei sus, jos, stanga, dreapta apasata). Nu se vor folosi biblioteci de functii, jQuery, pluginuri, etc.Puzzle-ul initial:
    
        3	8	9	5
        7	13	6	15
        10		14	4
        2	11	1	12
    
    Puzzle-ul rezolvat:

        1	2	3	4
        5	6	7	8
        9	10	11	12
        13	14	15	
    Cerinta facultativa pentru cei ce se “plictisesc” :): Dupa implementarea initiala, se va crea o a doua varianta a jocului, unde, in loc de numere, celulele tabelului vor contine sprite-uri CSS obtinute din cadrul unei aceleasi imagini patrate. Numarul n se va da la inceputul jocului, la fel si URL-ul imaginii ce se va folosi in sprite-urile CSS ca si fundal pe celulele tabelului. Nu se vor folosi biblioteci de functii, jQuery, pluginuri, etc.