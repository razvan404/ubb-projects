# Problema 4

Implementaţi următoarele scenarii pentru baza de date proprie:
- Creaţi 4 scenarii ce reproduc următoarele situaţii generate de execuţia concurentă: dirty reads, non-repeatable  reads, phantom  readsşi un deadlock. Puteţi implementa aceste scenarii atât ca proceduri stocate cât şi ca interogări de sine stătătoare. De asemenea, pentru fiecare dintre scenariile create, găsiţi soluţii de rezolvare/evitare aacestor situaţii. (6 puncte)
- Creaţi  un  scenariu  de deadlockprin  intermediul  unei  aplicaţii  .NET,  folosind multithreading. Va trebui ca două proceduri stocate/interogări să fie executate în 2 fire de execuţie diferite. Firul de execuţie ce eşuează din cauza deadlock-ului va trebui să fie reluat (stabiliţi un număr maxim de reluări până când procedura stocată/interogarea este considerată terminată fără succes - aborted). (3 puncte) 
Oficiu: 1 punct

Observaţie: Pentru toate scenariile trebuie să stabiliţi un sistem de logare ce vă va permite să memoraţi istoricul acţiunilor executate. Pentru detectarea erorilor se recomandă folosirea clauzei try-catch, atât în aplicaţia .NET cât şi în codul SQL.

Pentru prezentarea laboratorului pregătiţi explicaţii detaliate ale scenariilor şi implementării.

Link-uri utile:
- Cursul #2 şi seminarul #3
- http://msdn.microsoft.com/en-us/library/ms173763.aspx
- http://msdn.microsoft.com/en-us/library/ms174377.aspx
- http://www.albahari.com/threading/