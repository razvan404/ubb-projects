# <b>Tema 6 - AJAX</b>

<ol>
<li>
Sa se scrie o pagina HTML care contine doua liste cu statii de plecare si statii de sosire pentru trenuri. Server side se intretine o baza de date cu inregistrari de forma:

    (Oras1, Oras2)
    (Oras1, Oras3)
    (Oras2, Oras4)
    (Oras2, Oras5)
    (Oras6, Oras7)

    (Oras1, Oras2)
    (Oras1, Oras3)
    (Oras2, Oras4)
    (Oras2, Oras5)
    (Oras6, Oras7)
</li>
<li>
In momentul in care utilizatorul selecteaza o statie de plecare in prima componenta lista a doua se va actualiza folosind AJAX cu lista statiilor in care se poate ajunge din orasul selectat in prima lista.
</li>
<li>
O tabela dintr-o baza de date mentinuta server side are urmatoarele atribute: Nume, Prenume, Telefon, E-mail. Inregistrarile din aceasta tabela vor fi afisate pe client paginat cate 3 pe pagina, impreuna cu doua butoane Next si Previous. La actionarea butoanelor Next si Previous se vor afisa urmatoarele 3, respectiv anterioarele 3 inregistrari din baza de date, care vor fi aduse pe client pintr-un apel AJAX. Butoanele Next si Previous trebuie sa devina disabled daca in urma actionarii acestora nu se mai pot aduce inregistrari noi pe client.
</li>
<li>
Intr-o tabela a unei baze de date mentinuta server side exista inregistrari indexate dupa un anumit camp cheie (spre exemplu id). Sa se scrie o pagina HTML ce contine o lista ale caror valori sunt valorile atributului cheie. Pagina HTML contine si un formular care contine, pentru elementul selectat din lista, valorile corespunzatoare ale celorlalte atribute din baza de date. La modificarea elementului selectat in lista se vor actualiza valorile din formular. La modificarea valorilor din formular, un buton “Save” initial disabled va deveni activ, actionarea sa ducand la salvarea datelor server side. La modificarea datelor din formular si selectarea altui element cheie din lista fara salvarea datelor din formular, utilizatorul va fi atentionat ca datele s-au modificat si daca se doreste in prealabil salvarea acestora. Problema va fi implementata folosind AJAX.
</li>
<li>
Sa se scrie o pagina HTML care contine un tabel de 3×3 care reprezinta o tabla de X-0. Aleator va incepe sa joace fie calculatorul fie jucatorul. La un click intr-o casuta a tabelului acesta se va completa cu X sau 0 in funtie daca a inceput sau nu jucatorul uman. Dupa actiunea jucatorului se va apela prin AJAX un script server side care face urmatoarea mutare. Tot server side se va face verificarea terminarii jocului.
</li>
<li>
Folosind JavaScript sa se creea o componenta de tipul Tree-View. Nodurile acestei componente vor contine nume de directoare, iar frunzele nume de fisiere. Aceasta componenta va fi creata cu ajutorul AJAX si va reflecta structura de directoare server-side (la un click pe un nod director se va apela un script server side care va intoarce browserului continutul directorului respectiv). La un click pe un nod frunza (fisier) la un click pe acest fisier se va vizualiza in pagina HTML si continutul fisierului. Pe client, Tree-View-ul va fi implementat sub forma unei liste de liste (de liste, etc) create cu ajutorul tag-urilor &lt;ul&gt; si &lt;li&gt;.
</li>
<li>
Sa se scrie o pagina HTML care contine o serie de combo boxuri legate de proprietatile articolelor vandute intr-un magazin on-line IT. Sa se implementeze folosind AJAX un mecanism de filtrare a articolelor dorite de utilizator dupa proprietatile acestora. Spre exemplu, clientul va putea filtra notebookurile din baza de date dupa urmatoarele proprietati: producator, procesor, memorie, capacitate HDD, placa video, etc.
</li>
</ol>