# Problema 3

Implementaţi următoarele scenarii pentru baza de date proprie:

- Creaţi o procedură stocată ce inserează date pentru entităţi ce se află într-o relaţie m-n. Dacă o operaţie de inserare eşuează, trebuie făcut roll-backpe întreaga procedură stocată. (5 puncte)
- Creaţi o procedură stocată ce inserează date pentru entităţi ce se află într-o relaţie m-n. Dacă o operaţie de inserare eşuează va trebui să se păstreze cât mai mult posibil din ceea ce s-a modificat până în acel moment. De exemplu, dacă se încearcă inserarea unei cărţi şi a autorilor acesteia, iar autorii au fost inseraţi cu succes însă apare o problemă la inserarea cărţii, atunci să se facă roll-back la inserarea de carte însă autorii acesteia să rămână în baza de date. (4 puncte) 
- Oficiu: 1 punct

<b>Observaţie</b>: Ca notă generală, nu se va transmite niciun ID ca parametru de intrare a unei proceduri stocate şi toţi parametrii trebuie să fie validaţi (utilizaţi funcţii acolo unde este nevoie).

De asemenea, pentru toate scenariile trebuie să stabiliţi un sistem de logare ce vă va permite să memoraţi istoricul acţiunilor executate. Pentru detectarea erorilor se recomandă folosirea clauzei try-catch.

Pentru prezentarea laboratorului pregătiţi teste ce acoperă scenarii de succes şi cu erori. Pregătiţi explicaţii detaliate ale scenariilor şi implementării.

Link-uri utile:
- Cursul #2 şi seminarul #3
- http://msdn.microsoft.com/en-us/library/ms174377.aspx