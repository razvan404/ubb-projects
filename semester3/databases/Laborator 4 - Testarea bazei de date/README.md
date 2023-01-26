# Problema 4 - Testarea bazei de date

După finalizarea proiectării bazei de date, echipa de dezvoltare e interesată de obţinerea unor rezultate legate de performanţa acesteia. Pentru înregistrarea mai multor configuraţii de testare şi a rezultatelor rulării acestora se va creea următoarea structură relaţională:

- Tests – conţine informaţii despre diferite configuraţii de testare
- Tables – conţine listele tabelelor ce ar putea face parte din testare
- TestTables – este tabela de legătură dintre Tests şi Tables şi conţine lista tabelelor implicate în fiecare test
- Views – o muţime de view-uri existente în baza de date şi care sunt utilizate în testarea performanţei unor interogări particulare
- TestViews – este tabela de legătură dintre Tests şi Views şi conţine lista view-urilor implicate în fiecare test
- TestRuns – conţine rezultatele execuţiei diferitelor teste. Fiecare rulare de test presupune următoarele: 
    1) ştergerea datelor din tabelele asociate testului (în ordinea dată de câmpul Position); 
    2) inserarea înregistrărilor în tabele în ordinea inversă dată de Position (numărul de înregistrări inserate este dat de câmpul NoOfRows); 
    3) Evaluarea timpului de execuţie a view-urilor
- TestRunTables – conţine informaţii despre performanţa în care se inserării înregistrărilor fiecărei tabele asociate testului 
- TestRunViews – conţine informaţii despre performanţa fiecărei view din test

Se cere implementarea unor proceduri stocate de evaluare şi stocare a rezultatelor testărilor. Testul trebuie să fie disponibil pentru cel puţin trei tabele:

 - o tabelă având un câmp ca şi cheie primară şi nici o cheie străină,
 - o tabelă având un câmp ca şi cheie primară şi cel puţin o cheie străină,
 - o tabelă având două câmpuri ca şi cheie primară,

şi trei view-uri:

 - un view ce conţine o comandă SELECT pe o tabelă,
 - un view ce conţine o comandă SELECT aplicată pe cel puţin două tabele,
 - un view ce conţine o comandă SELECT aplicată pe cel puţin două tabele şi având o clauză GROUP BY.

Observaţie:
 Felul în care sunt implementate procedurile stocate şi/sau funcţiile este la latitudinea fiecăruia. Soluţiile care permit extinderea la noi tabele/view-uri cu un grad scăzut sau chiar fără codificare ulterioară vor fi apreciate în mod deosebit.
