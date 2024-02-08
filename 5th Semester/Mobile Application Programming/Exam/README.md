Imprumuturi

Pentru a-si gestiona lucrurile pe care le imprumuta intre ei (assets - ex. carti de joc, jocuri),
un grup de prieteni foloseste o aplicatie mobila si un server care ofera servicii REST 
despre aceste assets, un asset avand urmatoarele proprietati:
  - `id`: intreg pozitiv, ex. `1`
  - `name`: sir de caractere, ex. `a1`
  - `takenBy`: sir de caractere reprezentand numele utilizatorului care a imprumutat asset-ul, ex. `'u1'`
  - `desiredBy`: o lista de utilizatori care doresc sa imprumute asset-ul, ex. `['u2', 'u3']`
     Utilizatorii vor imprumuta in ordinea din aceasta lista.

Lista lucrurilor (array of assets) este trimisa de server catre clienti prin web socket (ws://localhost:3000).

Dezvoltati o aplicatie mobila dupa cum urmeaza.

1. La pornirea aplicatiei, un (prim) ecran permite utilizatorului sa-si introduca numele
   `username` si sa declanseze un buton `Next` pentru a naviga la al doilea ecran.
   La repornirea aplicatiei, daca in sesiunile anterioare de lucru utilizatorul a 
   declansat butonul 'Next', automat aplicatia navigheaza la al doilea ecran [1p].

2. In contextul celui de-al doilea ecran, aplicatia descarca lucrurile conectandu-se
   prin web soccket la server. Utilizatorul va fi notificat la terminarea descarcarii [1p].

3. Daca in sesiunile de lucru anterioare s-au descarcat lucruri, aplicatia le va prezenta
   imediat, neasteptand terminarea descarcarii de la puntul 3 [1p].

4. Lucrurile sunt prezentate intr-o lista, un element din lista va afisand numele lucrului
   `name` cu un background indicand starea lucrului relativ la utilizatorul curent:
   `red` daca lucrul este imprumutat de utilizatorul curent;
   `green` daca lucrul poate fi imprumutat imediat de utilizatorul curent;
   `yellow` daca utilizatorul face parte din lista `desiredBy`, dar nu este primul in lista;
   `white`, in caz contrar [1p].
   
5. Utilizatorul poate filtra lucrurile dupa starea lor (red, green, yellow, white) [1p].

6. Cand utilizatorul face click pe un element din lista, elementul se va expanda si va arata 
   valoarea proprietatii `desiredBy` si un buton: `Return` pentru elementele `red`,
   `Take` pentru `green`, `Remove request` pentru `yellow` entries, si `Add request`
   pentru `white` entries [1p]

7. Cand utilizatorul face click pe butoanele de la punctul (6), aplicatia va actualiza asset-ul
   via PATCH /asset/:id, incluzand in corpul cererii proprietatile `takenBy` si `desiredBy` [1p].

8. Daca operatia PATCH e efectuata cu succes, lista va fi actualizata corespunzator.
   Daca operatia PATCH esueaza, o notificare va fi afisata iar utilizatorul va putea relua operatia esuata [1p].

9. Serverul emite notificari prin ws pe localhost:3000. Notificarile indica faptul un
   un lucru a fost a fost actualizat sau creat [1p].
