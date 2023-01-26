# Problema 3 - Modificare bazei de date

Uneori, după proiectarea unei baze de date, este necesară actualizarea structurii 
acesteia; din păcate însă nu toate actualizările efectuate se dovedesc a fi corecte, 
si modificările trebuie să fie anulate. În acest context, se cere dezvoltarea unui 
mecanism de versionare care să faciliteze tranziţia de la o versiune a bazei de date 
la alta.

Scrieţi un script SQL care va:

- modifica tipul unei coloane;
- adauga o costrângere de “valoare implicită” pentru un câmp;
- creea/şterge o tabelă;
- adăuga un câmp nou;
- creea/şterge o constrângere de cheie străină.


Aceste scripturi pot fi generate, însă va trebui să puteţi explica structura lor.
Pentru fiecare dintre scripturile de mai sus scrieţi/generaţi un alt script care 
implementează inversul operaţiei. De asemenea, creaţi o nouă tabelă care să 
memoreze versiunea structurii bazei de date (presupunând că acestă versiune este 
pur şi simplu un număr întreg).

Creaţi pentru fiecare din scripturi câte o procedură stocată şi asiguraţi-vă ca numele 
acestora să fie simplu şi clar.

De asemenea, scrieţi o altă procedură stocată ce primeşte ca parametru un număr 
de versiune şi aduce baza de date la versiunea respectivă.
Referinţe utile:
- DDL: seminarul 1
- TSql: instrucţiuni SQL de bază (declare, begin, end, set etc.)
    - http://msdn.microsoft.com/en-us/library/ms190487.aspx
    - http://msdn.microsoft.com/en-us/library/ms188927.aspx
    - http://msdn.microsoft.com/en-us/library/ms189484.aspx 
- TSql: intrucţiunea WHILE (http://msdn.microsoft.com/enus/library/ms178642.aspx )
- TSql: interogări dinamice (http://msdn.microsoft.com/enus/library/ms188001.aspx )
- Proceduri stocate: http://msdn.microsoft.com/en-us/library/ms190782.aspx

Alte referinţe: 
- BOL: http://msdn.microsoft.com/en-us/library/ms130214(v=sql.100).aspx
- BOL Database Engine: http://msdn.microsoft.com/enus/library/ms187875(v=sql.100).asp