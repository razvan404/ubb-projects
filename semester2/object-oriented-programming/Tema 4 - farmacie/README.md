# Farmacie

Creați o aplicație care permite:
- gestiunea unei liste de medicamente. Medicament: denumire, preț, producător, substanța activa
- adăugare, ștergere, modificare și afișare medicamente
- căutare medicament
- filtrare medicamente după: preț, substanța activa
- sortare medicamente după: denumire, producător, substanța activa + preț

Introduceți posibilitatea de a crea un cos de închirieri. Utilizatorul poate crea 
interactiv o lista de cârti pe care dorește sa le închirieze.
Adăugați următoarele acțiuni (elemente de meniu):
- Golește cos: șterge toate cărțile din cos.
- Adaugă in cos: adaugă in cos o carte după titlu
- Generează cos: utilizatorul introduce numărul total de cârti, coșul se populează aleator cu cărți
- Export. Salvează cos in fișier: CVS sau HTML. Se face salvarea in fișier doar când s-a selectat acest meniu, coșul nu este persistent (la repornire aplicație coșul este din nou gol), utilizatorul introduce numele fișierului unde se  salvează la fiecare export. 

Cerințe generale:
- Creați o aplicație C++, folosiți paradigma orientat obiect
- Aplicația are interfața utilizator tip consola
- Utilizați procesul de dezvoltare bazat pe funcționalități (Feature driven development). Identificați funcționalitățile și planificați-le pe doua iterații
- Folosiți o arhitectură stratificata (UI / Services(GRASP Controller) / Repository).
- Creați clase pentru: Domain, Service, UI, Repository.
- Toate funcțiile necesare vor fi specificate și testate. (Test Code Coverage >99% la toate modulele in afara de UI)
- Fara warninguri (in Visual Studio warning level /W4, treat warning as errors)
- Const Correctness: folosiți calificativul const pentru variabile/parametrii care nu sunt modificații, folosiți calificativul const pentru metode care nu modifica starea obiectelor, transmiteți parametrii prin const & peste tot unde este posibil, evitați copierea obiectelor când nu este necesar.

Iterație 1: 
- Folosiți clasa std::string si clasa std::vector din STL (librăria standard C++)
- Nu folosiți pointeri.
- Nu alocați dinamic.

Iterația 2: 
- Înlocuiți clasa std::vector cu o clasa proprie parametrizata (Template) care 
implementează o lista folosind structura de date lista înlănțuita sau vector 
dinamic (la alegere). 
- Validarea datelor. Utilizatorul este anunțat printr-un mesaj daca: introduce 
valori de intrare greșite; încearcă sa adauge o entitate de doua ori, încearcă 
sa șteargă / modifice o entitate inexistenta (se vor folosi excepții)
- Creați o diagramă UML a claselor pentru a schița arhitectura aplicației

Cerințe Iterația 3:
- Modificați aplicația: folosiți clasa vector din STL si înlocuiți toate for-urile din 
aplicație cu algoritmi din STL si varianta c++11 de for (range for)

Cerințe Iterația 4:
- Adăugați partea cu salvarea in fișiere pentru produse/filme/cărți, etc.
- Adăugați posibilitatea de undo pentru operațiile: adaugă, șterge si modifică. 
Pentru implementare folosiți moștenire si polimorfism: 
- Creați o clasa abstracta ActiuneUndo care are o singura metoda: doUndo. 
• Creați 3 clase derivate UndoAdauga, UndoSterge, UndoModifica care in 
metoda doUndo implementează partea care reface situația de dinaintea 
adăugării/ștergerii/modificării.
- In controller se v-a tine o lista de ActiuniUndo care se pot executa in orice 
moment. Se va face un apel polimorfic la metoda doUndo.
- Acordați atenție gestiunii memoriei, evitați fenomenul de slicing

Timp de lucru 4 săptămâni