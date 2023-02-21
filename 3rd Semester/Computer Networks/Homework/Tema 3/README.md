# Tema 3

Sa se implementeze in C o pereche de programe client/server care comunica prin socket-uri UDP pentru rezolvarea urmatoarelor probleme:

1. Un client trimite unui server doua numere. Serverul va returna clientului suma celor doua numere.
2. Un client trimite unui server un numar. Serverul va returna clientului un boolean care sa indice daca numarul respective este prim sau nu.
3. Un client trimite unui server un sir de lugime cel mult 100 de caractere. Serverul va returna clientului numarul de caractere spatiu din sir.
4. Un client trimite unui server un sir de lungime cel mult 100 de caractere. Serverul va returna clientului acest sir oglindit (caracterele sirului in ordine inversa).
5. Un client trimite unui server un numar reprezentat pe un octet fara semn. Serverul va returna clientului sirul divizorilor acestui numar.
6. Un client trimite unui server un sir de lungime cel mult 100 de caractere si un caracter. Serverul va returna clientului toate pozitiile pe care caracterul primit se regaseste in sir.
7. Un client trimite unui server un sir de lungime cel mult 100 de caractere si doua numere (fie acestea s, i, l). Serverul va returna clientului subsirul de lungime l a lui s care incepe la pozitia i.
8. Un client trimite unui server doua numere reprezentate pe doi octeti fara semn fiecare. Serverul va returna clientului cmmdc si cmmmc al numerelor primite.
9. Un client trimite unui server o cerere prin care ii cere acestuia data si ora curenta. Serverul va returna clientului data sub forma unui intreg ce reprezinta numarul de secunde trecute de la 1 ianuarie 1970. Clientul va afisa corespunzator data pe baza acestui intreg.
10. Un client trimite unui server un nume de calculator sub forma unui sir de caractere de lungime cel mult 100. Serverul va returna clientului un numar reprezentat pe 4 octeti fara semn ce reprezinta adresa IP a calculatorului respectiv. Clientul va afisa corespunzator adresa IP (in format zecimal cu “.”) sau un mesaj de eroare daca numele calculatorului nu poate fi translatat intr-o adresa IP.